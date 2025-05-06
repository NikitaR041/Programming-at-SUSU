using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TesstMyBD
{
    public partial class Test1Form : Form
    {
        private string connestionString;
        public Test1Form(string ds)
        {
            InitializeComponent();
            connestionString = ds;
        }

        //Кнопка `добавить` - добавление содержимого в таблицу
        private void button1_Click(object sender, EventArgs e) {
        var units = new List<string>
        {
            "штука",
            "литр",
            "кг",
            "тонна",
            "пара",
            "bottle",
            "метр"
        };

        try{
            using (SqlConnection conn = new SqlConnection(connestionString))
            {
                conn.Open();
                foreach (var unit in units)
                {
                    string query = "INSERT INTO MeasUnit (MeasUnitName) VALUES (@name)";
                    SqlCommand cmd = new SqlCommand(query, conn);
                    cmd.Parameters.AddWithValue("@name", unit);
                    cmd.ExecuteNonQuery();
                }
                MessageBox.Show("Все записи успешно добавлены!");
                LoadMeasUnits();
            }
        }
        catch (Exception ex) {
            MessageBox.Show("Ошибка при добавлении: " + ex.Message);
            }
        }

        //Конпка `отобразить` - отображение содержимого из таблицы в элемент dataGridView1
        private void button2_Click(object sender, EventArgs e)
        {
            LoadMeasUnits(); //Отображение 
        }
        private void LoadMeasUnits()
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connestionString))
                {
                    //conn.Open();
                    //SqlDataAdapter adapter = new SqlDataAdapter("SELECT * FROM MeasUnit", conn);
                    //DataTable table = new DataTable();
                    //adapter.Fill(table);
                    //dataGridView1.DataSource = table;

                    conn.Open();
                    SqlDataAdapter adapter = new SqlDataAdapter("select * from MeasUnit", conn);
                    DataSet ds1 = new DataSet();
                    adapter.Fill(ds1);
                    dataGridView1.DataSource = ds1.Tables[0];
                    dataGridView1.AutoResizeColumns();
                    dataGridView1.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка загрузки: " + ex.Message);
            }
        }


        //Кнопка по переходу к новой форме
        private void button3_Click(object sender, EventArgs e)
        {
            Test2Form form2 = new Test2Form(connestionString);
            form2.Show();
        }

        //Конпка `удалить` - удаление содержимого из таблицы 
        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connestionString))
                {
                    conn.Open();
                    string query = "DELETE FROM MeasUnit";
                    SqlCommand cmd = new SqlCommand(query, conn);
                    int rowsAffected = cmd.ExecuteNonQuery();
                    MessageBox.Show($"Удалено записей: {rowsAffected}");
                    LoadMeasUnits(); // обновляем таблицу на форме
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при удалении: " + ex.Message);
            }
        }
    }
}
