/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: glib.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/02/16 06:14:27
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/02/16                  build this moudle  
 ***************************************************************************************/

#include <glib-2.0/glib.h>
#include <locale.h>

gint counter1 = 10;
gint counter2 = 10;
GMainLoop* loop;
gboolean callback(gpointer arg)
{
    g_print("call back\n");
	//g_message("中文");
	//fflush();
    if(--counter1 ==0){
        g_print("\n");
        //退出循环
        g_main_loop_quit(loop);
        //注销定时器
        return FALSE;
    }

	g_print ( "count1 is %d\n", counter1 );
    //定时器继续运行
    return TRUE;
}

gboolean callback2(gpointer arg)
{
    g_print("call back2\n");
	//g_message("中文");
	//fflush();
    if(--counter2 ==0){
        g_print("\n");
        //退出循环
        g_main_loop_quit(loop);
        //注销定时器
        return FALSE;
    }

	g_print ( "count2 is %d\n", counter2 );
    //定时器继续运行
    return TRUE;
}

int main(int argc, char* argv[])
{
    setlocale (LC_ALL, "");/*将程序的locale设置成与console的一致*/
    //g_thread_init是必需的，GMainLoop需要gthread库的支持。
    if(g_thread_supported() == 0)
        g_thread_init(NULL);
    //创建一个循环体，先不管参数的意思。
    g_print("g_main_loop_new\n");
    loop = g_main_loop_new(NULL, FALSE);

   //增加一个定时器，100毫秒运行一次callback
    g_timeout_add(1000, callback, NULL);
	sleep(2);
    g_timeout_add(2000, callback2, NULL);
    g_print("g_main_loop_run\n");
    g_main_loop_run(loop);
    g_print("g_main_loop_unref\n");
    g_main_loop_unref(loop);
    return 0;
}

//GMainLoop* loop;
//int main(int argc, char* argv[])
//{
//    //g_thread_init是必需的，GMainLoop需要gthread库的支持。
//    if(g_thread_supported() == 0)
//        g_thread_init(NULL);
//    //创建一个循环体，先不管参数的意思。
//    g_print("g_main_loop_new\n");
//    loop = g_main_loop_new(NULL, FALSE);
//    //让这个循环体跑起来
//    g_print("g_main_loop_run\n");
//    g_main_loop_run(loop);
//    //循环运行完成后，计数器减一
//    //glib的很多结构类型和c++的智能指针相似，拥有一个计数器
//    //当计数器为0时，自动释放资源。
//    g_print("g_main_loop_unref\n");
//    g_main_loop_unref(loop);
//    return 0;
//}
//
