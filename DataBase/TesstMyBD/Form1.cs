using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//Подключение к копиям бд
using System.Data.SqlClient;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Security.Cryptography;

namespace TesstMyBD
{
    public partial class Form1 : Form
    {
        private static string DS = "Database = Stud_WareHouse; User ID = Stud; Password = New20@%PSW;";

        public Form1()
        {

            InitializeComponent();

        }
            private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (checkBox1.Checked == true)
            {
                DS = DS.Insert(0, "Data Source = susu.prima.susu.ac.ru, 51435; ");
            }
            else
            {
                DS = DS.Insert(0, "Data Source = MSSQL-2K8\\MSSQL_K; ");
            }
            using (SqlConnection connection = new SqlConnection(DS))
            {
                connection.Open();
                MessageBox.Show($"Свойства подключения:\n" +
                $"\tСтрока подключения: {connection.ConnectionString}\n" +
                $"\tБаза данных: {connection.Database}\n" +
                $"\tСервер: {connection.DataSource}\n" +
                $"\tВерсия сервера: {connection.ServerVersion}\n" +
                $"\tСостояние: {connection.State}\n" +
                $"\tWorkstationld: {connection.WorkstationId}");
            }

            using (SqlConnection Connection = new SqlConnection(@DS))
            {
                Connection.Open();
                string MeasUnitName = "руб";
                SqlDataAdapter adapter = new SqlDataAdapter("SELECT \r\n    T.Tovar_ID,\r\n    T.TovarName,\r\n    T.IsTovar,\r\n    T.Amount,\r\n    T.Price,\r\n    T.Photo,\r\n    T.MeasUnit_ID,\r\n    M.MeasUnitName,\r\n    T.Parent_ID,\r\n    (T.Amount * T.Price) AS SumCost\r\nFROM \r\n    Tovar T\r\nJOIN \r\n    MeasUnit M ON T.MeasUnit_ID = M.MeasUnit_ID\r\nWHERE \r\n    M.MeasUnitName = @MeasUnitName AND T.IsTovar = 1;\r\n", Connection);
               
                DataSet ds1 = new DataSet();
                adapter.Fill(ds1);
                dataGridView1.DataSource = ds1.Tables[0];
                dataGridView1.AutoResizeColumns();
                dataGridView1.AutoSizeColumnsMode =
                DataGridViewAutoSizeColumnsMode.AllCells;
            }

        }

        private void Form1_Click(object sender, EventArgs e)
        {

        }
    }
}
