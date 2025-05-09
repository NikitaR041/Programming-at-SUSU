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

                    this.Hide(); // Скрываем главную форму  

                    // Открываем новое окно
                    Test1Form testForm = new Test1Form(DS); // Передаем строку подключения
                    testForm.ShowDialog();

                    
                    this.Close(); // Закрывать главную форму
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка подключения: " + ex.Message);
            }
        }
    }
}
