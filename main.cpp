#include <iostream>
#include <iostream>
#include <string>
extern "C" {

#include <libavformat/avformat.h>

}
const char* func() {
	char* filename; 
    filename =(char*)malloc(sizeof(char) * 1024);
	FILE *f = popen("zenity --file-selection", "r");
	fgets(filename, 1024, f);
	char *copy = strdup(filename);
	copy[strlen(copy) - 1] = 0;
	const char* save = copy;
    return (save);
}

int main()
{
double fps=0;
std::string path;
av_register_all();
avformat_network_init();
const char *buf = func();
std::cout<<buf<<std::endl;
AVFormatContext *formatCtx = avformat_alloc_context();
if(avformat_open_input(&formatCtx,buf, nullptr, nullptr) !=0)
{
//	std::cout<<buf<<std::endl;
	std::cout<<"Не удалось открыть файл."<<std::endl;
return -1;
}
	avformat_find_stream_info(formatCtx, NULL);
	int count_streams = formatCtx->nb_streams;
	std::cout<<"Количество потоков: "<<count_streams<<std::endl;

for (int i=0; i<formatCtx->nb_streams; i++)
{
	AVCodecParameters *codec_params = formatCtx->streams[i]->codecpar;
	if(codec_params->codec_type == AVMEDIA_TYPE_AUDIO)
	{
	std::cout<<"Тип аудиокодека: " << avcodec_get_name(codec_params->codec_id)<<std::endl;
	}
	else 
		if (codec_params->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			std::cout<<"Тип видео кодека: " << avcodec_get_name(codec_params->codec_id)<<std::endl;
			int duration = formatCtx->duration / AV_TIME_BASE;
			int hours = duration / 3600;
			int minutes = (duration % 3600) / 60;
			int seconds = duration % 60;
            std::cout << "Продолжительность видео: " << hours << ":" << minutes << ":" << seconds << std::endl;
		}
	fps = av_q2d(formatCtx->streams[i]->r_frame_rate);
	
}

std::cout<<"Количество кадров: " <<fps<<std::endl;
avformat_close_input(&formatCtx);
avformat_free_context(formatCtx);

return 0;
}
