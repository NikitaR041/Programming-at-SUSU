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

        private void Test1Form_Load(object sender, EventArgs e)
        {
            LoadMeasUnitsToComboBox();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        //Кнопка `добавить` - добавление содержимого в таблицу
        private void button1_Click(object sender, EventArgs e)
        {
            string newUnit = textBox2.Text.Trim();

            if (string.IsNullOrWhiteSpace(newUnit))
            {
                MessageBox.Show("Введите название единицы измерения.");
                return;
            }

            try
            {
                using (SqlConnection conn = new SqlConnection(connestionString))
                {
                    conn.Open();
                    string query = "INSERT INTO MeasUnit (MeasUnitName) VALUES (@name)";
                    SqlCommand cmd = new SqlCommand(query, conn);
                    cmd.Parameters.AddWithValue("@name", newUnit);
                    cmd.ExecuteNonQuery();
                    MessageBox.Show("Единица успешно добавлена!");
                    LoadMeasUnits(); // Обновим DataGridView и ComboBox
                    LoadMeasUnitsToComboBox();
                }
            }
            catch (SqlException ex)
            {
                if (ex.Number == 2627) // дублирование уникального значения
                    MessageBox.Show("Такая единица измерения уже существует.");
                else
                    MessageBox.Show("Ошибка при добавлении: " + ex.Message);
            }
        }

        //Конпка `отобразить` - отображение содержимого из таблицы в элемент dataGridView1
        private void button2_Click(object sender, EventArgs e)
        {
            LoadMeasUnits(); //Отображение 
        }

        //Конпка `удалить` - удаление содержимого из таблицы 
        private void button4_Click(object sender, EventArgs e)
        {
            string unitToDelete = textBox3.Text.Trim();

            if (string.IsNullOrWhiteSpace(unitToDelete))
            {
                MessageBox.Show("Введите название единицы измерения для удаления.");
                return;
            }

            try
            {
                using (SqlConnection conn = new SqlConnection(connestionString))
                {
                    conn.Open();
                    string query = "DELETE FROM MeasUnit WHERE MeasUnitName = @name";
                    SqlCommand cmd = new SqlCommand(query, conn);
                    cmd.Parameters.AddWithValue("@name", unitToDelete);
                    int affectedRows = cmd.ExecuteNonQuery();

                    if (affectedRows > 0)
                        MessageBox.Show("Единица успешно удалена!");
                    else
                        MessageBox.Show("Такой единицы измерения не найдено.");

                    LoadMeasUnits(); // Обновим таблицу
                    LoadMeasUnitsToComboBox();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при удалении: " + ex.Message);
            }
        }

        //Кнопка `обновить` - изменение старого содержимого на нового 
        private void button5_Click(object sender, EventArgs e)
        {
            string currentUnit = textBox4.Text.Trim();  // Текущее название
            string newUnit = textBox5.Text.Trim();      // Новое название

            if (string.IsNullOrWhiteSpace(currentUnit) || string.IsNullOrWhiteSpace(newUnit))
            {
                MessageBox.Show("Введите текущее и новое название единицы измерения.");
                return;
            }

            try
            {
                using (SqlConnection conn = new SqlConnection(connestionString))
                {
                    conn.Open();
                    string query = "UPDATE MeasUnit SET MeasUnitName = @newName WHERE MeasUnitName = @currentName";
                    SqlCommand cmd = new SqlCommand(query, conn);
                    cmd.Parameters.AddWithValue("@newName", newUnit);
                    cmd.Parameters.AddWithValue("@currentName", currentUnit);


                    //Проверка на количество строк, на которые повлиял запрос
                    int affectedRows = cmd.ExecuteNonQuery();
                    if (affectedRows > 0)
                    {
                        MessageBox.Show("Единица измерения успешно обновлена!");
                        LoadMeasUnits(); // Обновим таблицу
                        LoadMeasUnitsToComboBox();
                    }
                    else
                    {
                        MessageBox.Show("Единица измерения с таким названием не найдена.");
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при обновлении: " + ex.Message);
            }
        }

        //Конпка `Отобразить товары из категории` - отображение товаров по категории в элемент dataGridView1
        private void button6_Click(object sender, EventArgs e)
        {
            string selectedUnit = comboBox1.SelectedItem?.ToString();

            if (string.IsNullOrWhiteSpace(selectedUnit))
            {
                MessageBox.Show("Пожалуйста, выберите единицу измерения.");
                return;
            }

            try
            {
                using (SqlConnection conn = new SqlConnection(connestionString))
                {
                    conn.Open();
                    string query = @"
                        SELECT T.TovarName
                        FROM Tovar T
                        JOIN MeasUnit M ON T.MeasUnit_ID = M.MeasUnit_ID
                        WHERE M.MeasUnitName = @unitName";

                    SqlCommand cmd = new SqlCommand(query, conn);
                    cmd.Parameters.AddWithValue("@unitName", selectedUnit);

                    SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                    DataTable dt = new DataTable();
                    adapter.Fill(dt);

                    dataGridView1.DataSource = dt;
                    dataGridView1.AutoResizeColumns();
                    dataGridView1.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при получении товаров: " + ex.Message);
            }
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
        private void LoadMeasUnitsToComboBox()
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connestionString))
                {
                    conn.Open();
                    string query = "SELECT MeasUnitName FROM MeasUnit";
                    SqlCommand cmd = new SqlCommand(query, conn);
                    SqlDataReader reader = cmd.ExecuteReader();

                    comboBox1.Items.Clear();
                    while (reader.Read())
                    {
                        comboBox1.Items.Add(reader.GetString(0));
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при загрузке единиц измерения: " + ex.Message);
            }
        }

    }
}
