using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class AudioSpeaker
    {
        private string name_audio_speaker; //Название аудиоколонки
        private string power_speaker; //Мощность аудиоколонки
        private string size_speaker; //Размеры аудиоколонки
        private string connection_type; //Тип соединения аудиоколонки
        private string battery_life; //Время работы от батареи аудиоколонки
        private string price; //Цена аудиоколонки

        //Конструктор
        public AudioSpeaker() { }
        public AudioSpeaker(string name_audio_speaker, string power_speaker, string size_speaker, string connection_type, string battery_life, string price)
        {
            this.name_audio_speaker = name_audio_speaker;
            this.power_speaker = power_speaker;
            this.size_speaker = size_speaker;
            this.connection_type = connection_type;
            this.battery_life = battery_life;
            this.price = price;
        }
        
        //Создаем Property - аксессор и геттер
        public string Name { 
            get { 
                return this.name_audio_speaker; 
            }
            set {
                this.name_audio_speaker = value;
            }
        }

        public string Power { 
            get { 
                return this.power_speaker; 
            }
            set { 
                this.power_speaker = value;
            }
        }

        public string Size { 
            get { 
                return this.size_speaker; 
            }
            set {
                this.size_speaker = value;
            }
        }

        public string ConType { 
            get { 
                return this.connection_type;
            }
            set {
                this.connection_type = value; 
            }
        }

        public string ButteryLife { 
            get { 
                return this.battery_life; 
            }
            set {
                this.battery_life = value;
            }
        }

        public string Price {
            get {
                return this.price;
            }
            set { 
                this.price = value;
            }
        }

        //Возможно нужно переопределить ToString()
        public override string ToString()
        {
            //return $"Название: {name_audio_speaker}\n, Мощность: {power_speaker}\n, Размер: {size_speaker}\n, Тип соединения: {connection_type}\n, Время работы: {battery_life}\n, Цена: {price}\n";
            return $"{Name,-26}|{Power,-16}|{Size,-21}|{ConType,-16}|{ButteryLife,-22}|{Price,0}";
        }
    }
}
