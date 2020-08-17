package com.example.fairy.guardianclient02;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 * Created by Fairy on 2015-11-25.
 */

public class HeartBeatManager extends BroadcastReceiver
{
    final byte[] EmbedKey = {
            (byte)0x88, (byte)0xE3, (byte)0x4F, (byte)0x8F, (byte)0x08, (byte)0x17, (byte)0x79, (byte)0xF1,
            (byte)0xE9, (byte)0xF3, (byte)0x94, (byte)0x37, (byte)0x0A, (byte)0xD4, (byte)0x05, (byte)0x89
    };
    final byte[] EmbedIV = {
            (byte)0x26, (byte)0x8D, (byte)0x66, (byte)0xA7, (byte)0x35, (byte)0xA8, (byte)0x1A, (byte)0x81,
            (byte)0x6F, (byte)0xBA, (byte)0xD9, (byte)0xFA, (byte)0x36, (byte)0x16, (byte)0x25, (byte)0x01
    };

    //ini를 대신할 UI설정 저장 객체
    SharedPreferences GuardianInfo;
    @Override
    public void onReceive(Context context, Intent intent)
    {
        GuardianInfo = context.getSharedPreferences("GuardianInfo", Context.MODE_MULTI_PROCESS);    //프리퍼런스 Get객체
        UDPSend();
    }

    public void UDPSend() {
        new Thread(new Runnable() {
            public void run() {
                try {
                    InetAddress targetAddr = InetAddress.getByName(GuardianInfo.getString("IP", "192.168.0.2"));
                    DatagramSocket socket = new DatagramSocket();
                    byte[] buf = ("TYPE=AUTOLOCK:ID="+IDEncrypt()+":COMMAND=INIT:").getBytes();
                    DatagramPacket packet = new DatagramPacket(buf, buf.length, targetAddr, 8787);
                    socket.send(packet);
                    socket.close();
                } catch (Exception e) {
                }
            }
        }).start();
    }

    //(Start)암호화 보조함수
    //현재 키로 ID암호화+타임스템프 붙이기(등록이 완료 된 후 호출 가능)
    public String IDEncrypt()
    {
        String TempIDAttached = attachTimeStamp(GuardianInfo.getString("ID", "123,123"));
        byte[] byteKey = StrNumToByte(GuardianInfo.getString("KEY", "123,123"));
        byte[] byteID = StrNumToByte(TempIDAttached);

        byte[] encryptID = KISA_SEED_CBC.SEED_CBC_Encrypt(byteKey, EmbedIV, byteID, 0, byteID.length);

        return ByteToStrNum(encryptID);
    }


    public String attachTimeStamp(String str)
    {
        int TimeStamp = Integer.parseInt(new java.text.SimpleDateFormat("yyyy").format(new java.util.Date())) +
                Integer.parseInt(new java.text.SimpleDateFormat("MM").format(new java.util.Date())) +
                Integer.parseInt(new java.text.SimpleDateFormat("dd").format(new java.util.Date())) +
                Integer.parseInt(new java.text.SimpleDateFormat("HH").format(new java.util.Date())) +
                Integer.parseInt(new java.text.SimpleDateFormat("mm").format(new java.util.Date()));
        str = str + (TimeStamp >> 8) + ",";   //상위 8비트
        str = str + (TimeStamp & 0x00FF) + ",";   //하위 8비트

        return str;
    }

    public byte[] StrNumToByte(String str)
    {
        int byteSize=0;
        for(int i=0;i<str.length();i++)
        {
            if(str.charAt(i) == ',')
                byteSize++;
        }
        byte[] result = new byte[byteSize];
        for(int i=0 ; i< byteSize; i++)
        {
            int num = Integer.valueOf(str.split(",")[i]);
            result[i] = (byte)num;
        }
        return result;
    }
    public String ByteToStrNum(byte str[])
    {
        String result = new String();
        for(int i=0 ; i<str.length ; i++)
        {
            if(str[i] < 0)
                result = result + (str[i] + 256) + ",";
            else
                result = result + (str[i]) + ",";
        }
        return result;
    }
    //(End)암호화 보조함수
}