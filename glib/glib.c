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
	//g_message("����");
	//fflush();
    if(--counter1 ==0){
        g_print("\n");
        //�˳�ѭ��
        g_main_loop_quit(loop);
        //ע����ʱ��
        return FALSE;
    }

	g_print ( "count1 is %d\n", counter1 );
    //��ʱ����������
    return TRUE;
}

gboolean callback2(gpointer arg)
{
    g_print("call back2\n");
	//g_message("����");
	//fflush();
    if(--counter2 ==0){
        g_print("\n");
        //�˳�ѭ��
        g_main_loop_quit(loop);
        //ע����ʱ��
        return FALSE;
    }

	g_print ( "count2 is %d\n", counter2 );
    //��ʱ����������
    return TRUE;
}

int main(int argc, char* argv[])
{
    setlocale (LC_ALL, "");/*�������locale���ó���console��һ��*/
    //g_thread_init�Ǳ���ģ�GMainLoop��Ҫgthread���֧�֡�
    if(g_thread_supported() == 0)
        g_thread_init(NULL);
    //����һ��ѭ���壬�Ȳ��ܲ�������˼��
    g_print("g_main_loop_new\n");
    loop = g_main_loop_new(NULL, FALSE);

   //����һ����ʱ����100��������һ��callback
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
//    //g_thread_init�Ǳ���ģ�GMainLoop��Ҫgthread���֧�֡�
//    if(g_thread_supported() == 0)
//        g_thread_init(NULL);
//    //����һ��ѭ���壬�Ȳ��ܲ�������˼��
//    g_print("g_main_loop_new\n");
//    loop = g_main_loop_new(NULL, FALSE);
//    //�����ѭ����������
//    g_print("g_main_loop_run\n");
//    g_main_loop_run(loop);
//    //ѭ��������ɺ󣬼�������һ
//    //glib�ĺܶ�ṹ���ͺ�c++������ָ�����ƣ�ӵ��һ��������
//    //��������Ϊ0ʱ���Զ��ͷ���Դ��
//    g_print("g_main_loop_unref\n");
//    g_main_loop_unref(loop);
//    return 0;
//}
//
