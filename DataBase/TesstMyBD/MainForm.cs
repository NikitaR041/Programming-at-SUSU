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
    public partial class MainForm : Form
    {
        //Строка подключения
        private static string DS = "Database = Stud_WareHouse; User ID = Stud; Password = New20@%PSW;";

        public MainForm()
        {
            //Методы
            InitializeComponent(); //По умолчанию - инициализация
            InitSetup(); //Собственное - отображение текста

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
            try
            {
                using (SqlConnection connection = new SqlConnection(DS))
                {
                    connection.Open();
                    MessageBox.Show("Успешное подключение к базе данных!");

                    // Открываем новое окно
                    Test1Form testForm = new Test1Form(DS); // Передаем строку подключения
                    testForm.Show();

                    //this.Hide(); // Скрываем форму подключения
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка подключения: " + ex.Message);
            }

            //using (SqlConnection connection = new SqlConnection(DS))
            //{
            //    connection.Open();
            //    MessageBox.Show($"Свойства подключения:\n" +
            //    $"\tСтрока подключения: {connection.ConnectionString}\n" +
            //    $"\tБаза данных: {connection.Database}\n" +
            //    $"\tСервер: {connection.DataSource}\n" +
            //    $"\tВерсия сервера: {connection.ServerVersion}\n" +
            //    $"\tСостояние: {connection.State}\n" +
            //    $"\tWorkstationld: {connection.WorkstationId}");
            //}

            //using (SqlConnection Connection = new SqlConnection(@DS))
            //{
            //    Connection.Open();
            //    string MeasUnitName = "руб";
            //    SqlDataAdapter adapter = new SqlDataAdapter("SELECT \r\n    T.Tovar_ID,\r\n    T.TovarName,\r\n    T.IsTovar,\r\n    T.Amount,\r\n    T.Price,\r\n    T.Photo,\r\n    T.MeasUnit_ID,\r\n    M.MeasUnitName,\r\n    T.Parent_ID,\r\n    (T.Amount * T.Price) AS SumCost\r\nFROM \r\n    Tovar T\r\nJOIN \r\n    MeasUnit M ON T.MeasUnit_ID = M.MeasUnit_ID\r\nWHERE \r\n    M.MeasUnitName = @MeasUnitName AND T.IsTovar = 1;\r\n", Connection);
               
            //    DataSet ds1 = new DataSet();
            //    adapter.Fill(ds1);
            //    dataGridView1.DataSource = ds1.Tables[0];
            //    dataGridView1.AutoResizeColumns();
            //    dataGridView1.AutoSizeColumnsMode =
            //    DataGridViewAutoSizeColumnsMode.AllCells;
            //}

        }

        private void InitSetup()
        {
            var lblText = new Label
            {
                Text = "Лабораторная работа",
                AutoSize = true,
                Location = new Point(this.Width / 2 - 120, 20),

            };
            this.Controls.Add(lblText);
        }
        //private void Form1_Click(object sender, EventArgs e)
        //{

        //}

        //private void checkBox1_CheckedChanged(object sender, EventArgs e)
        //{

        //}
    }
}
