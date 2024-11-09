using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
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
        private byte price; //Цена аудиоколонки

        public AudioSpeaker(string name_audio_speaker, string power_speaker, string counsize_speakertry, string connection_type, string battery_life, byte price)
        {
            this.name_audio_speaker = name_audio_speaker;
            this.power_speaker = power_speaker;
            this.size_speaker = size_speaker;
            this.connection_type = connection_type;
            this.battery_life = battery_life;
            this.price = price;
        }



    }
}
