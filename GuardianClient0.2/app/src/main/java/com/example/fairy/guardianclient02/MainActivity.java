package com.example.fairy.guardianclient02;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Handler;
import android.os.Message;
import android.os.PowerManager;
import android.os.SystemClock;
import android.os.Vibrator;

import android.os.Bundle;
import android.provider.ContactsContract;
import android.telephony.TelephonyManager;
import android.text.InputFilter;
import android.text.Spanned;

import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Calendar;
import java.util.regex.Pattern;

public class MainActivity extends Activity {

    //(Start)전역상수
    public static final int UI_LOCK = 0;
    public static final int UI_UNLOCK = 1;
    //내장 암호 키, 초기화벡터
    final byte[] EmbedKey = {
            (byte)0x88, (byte)0xE3, (byte)0x4F, (byte)0x8F, (byte)0x08, (byte)0x17, (byte)0x79, (byte)0xF1,
            (byte)0xE9, (byte)0xF3, (byte)0x94, (byte)0x37, (byte)0x0A, (byte)0xD4, (byte)0x05, (byte)0x89
    };
    final byte[] EmbedIV = {
            (byte)0x26, (byte)0x8D, (byte)0x66, (byte)0xA7, (byte)0x35, (byte)0xA8, (byte)0x1A, (byte)0x81,
            (byte)0x6F, (byte)0xBA, (byte)0xD9, (byte)0xFA, (byte)0x36, (byte)0x16, (byte)0x25, (byte)0x01
    };
    //(End)전역상수

    //(Start)공용객체 선언
    //<--프리퍼런스-->
    SharedPreferences GuardianInfo;
    SharedPreferences.Editor GuardianInfo_Editor;

    //<--바이브레이터-->
    Vibrator vibrator;

    //<--알람매니저-->
    Intent Alarm_intent;
    PendingIntent Alarm_sender;
    AlarmManager Alarm_HeartBeat;

    //<--파워매니저-->
    PowerManager powerManager;

    //<--휴대폰 번호-->
    String PhoneNumber;

    //<--소켓-->
    InetAddress ServerAddr;
    DatagramSocket UDPSocket;

    //<--UI핸들러-->
    UIHandlerMessageQueue UIHandler;

    //<--KEY/ID-->
    String TempKey;  //임시 키(서버에서 OK사인이 떨어지면 프리퍼런스에 저장)
    String TempID; //임시 값(서버에서 OK사인이 떨어지면 프리퍼런스에 저장)
    //(End)공용객체 선언


    //(Start)레이아웃 객체 변수 선언
    //<--탭-->
    ImageButton tab_Lock;
    ImageButton tab_Setup;
    LinearLayout page_Lock;

    //<--Lock페이지-->
    LinearLayout page_Setup;
    Switch lock_AutoLocking;
    TextView lock_autoLockingText;
    ImageButton lock_operatingLock;

    //<--Setup페이지-->
    EditText setup_TextIP;
    Button setup_SaveIP;
    Button setup_Register;
    //(End)레이아웃 객체 변수 선언

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTheme(android.R.style.Theme_NoTitleBar);

        //(Start)공용객체 할당
        //<--프리퍼런스-->
        GuardianInfo = getSharedPreferences("GuardianInfo", 0);    //프리퍼런스 Get객체
        GuardianInfo_Editor = GuardianInfo.edit();                      //프리퍼런스 Set객체

        //<--바이브레이터-->
        vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);

        //<--알람매니저-->
        Alarm_intent = new Intent(this, HeartBeatManager.class);//알람매니저를 등록할 인텐트 만들기
        Alarm_sender = PendingIntent.getBroadcast(this, 0, Alarm_intent, 0);//인텐트에 알람매니저 브로드캐스트 등록
        Alarm_HeartBeat = (AlarmManager) getSystemService(Context.ALARM_SERVICE);//알람매니저 객체생성

        //<--파워매니저-->
        powerManager = (PowerManager)getSystemService(POWER_SERVICE);          //절전방지 PowerManager

        //<--소켓-->
        try
        {
            ServerAddr = InetAddress.getByName(GuardianInfo.getString("IP", "192.168.0.2"));
            UDPSocket = new DatagramSocket();
        }
        catch (UnknownHostException e)
        {
            e.printStackTrace();
        }
        catch (SocketException e)
        {
            e.printStackTrace();
        }

        //<--UI핸들러-->
        UIHandler = new UIHandlerMessageQueue();  //UI핸들러

        //(End)공용객체 할당

        //(Start)레이아웃 객체 할당
        //<--탭-->
        tab_Lock = (ImageButton)findViewById(R.id.tab_Lock);
        tab_Setup = (ImageButton)findViewById(R.id.tab_Setup);
        page_Setup = (LinearLayout)findViewById(R.id.page_Setup);

        //<--Lock페이지-->
        page_Lock = (LinearLayout)findViewById(R.id.page_Lock);
        lock_AutoLocking = (Switch)findViewById(R.id.lock_autoLocking);
        lock_autoLockingText = (TextView)findViewById(R.id.lock_autoLockingText);
        lock_operatingLock = (ImageButton)findViewById(R.id.lock_operatingLock);

        //<--Setup페이지-->
        setup_TextIP = (EditText)findViewById(R.id.setup_TextIP);
        setup_SaveIP = (Button)findViewById(R.id.setup_SaveIP);
        setup_Register = (Button)findViewById(R.id.setup_Register);
        //(End)레이아웃 객체 할당


        //(Start)공용객체 초기설정
        //<--절전방지-->
        PowerManager.WakeLock wakeLock = powerManager.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, "wakelock"); //절전방지 WakeLock
        wakeLock.acquire();

        //<--휴대폰번호 가져오기-->
        TelephonyManager systemService = (TelephonyManager)getSystemService(Context.TELEPHONY_SERVICE);
        PhoneNumber = systemService.getLine1Number();

        //<--소켓 메시지큐 스레드-->

        Thread myThread = new Thread(new Runnable() {
            public void run()
            {

                byte[] buf = new byte[128];
                while(true)
                {
                    try
                    {
                        DatagramPacket packet = new DatagramPacket(buf, buf.length);
                        UDPSocket.receive(packet);

                        String ReadMessage = new String(packet.getData(),0,packet.getLength());

                        if(!ReadMessage.isEmpty())
                        {
                            Log.d("Fairy", ReadMessage);
                            if(ReadMessage.equals("LOCK"))
                                UIHandler.sendMessage(UIHandler.obtainMessage(UI_LOCK));
                            else if(ReadMessage.equals("UNLOCK"))
                                UIHandler.sendMessage(UIHandler.obtainMessage(UI_UNLOCK));
                            else if(ReadMessage.equals("REGIST"))
                            {
                                GuardianInfo_Editor.putString("KEY", TempKey);
                                GuardianInfo_Editor.putString("ID", TempID);
                                GuardianInfo_Editor.commit();
                            }
                        }
                    }
                    catch (IOException e)
                    {
                        e.printStackTrace();
                    }
                }
            }
        });
        myThread.start();

        //(End)공용객체 초기설정

        //(Start)메뉴 초기설정
        View.OnTouchListener MenuListener = new View.OnTouchListener()
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (v.getId())
                {
                    case R.id.tab_Lock:
                        switch (event.getAction())
                        {
                            case MotionEvent.ACTION_UP:
                                tab_Lock.setSelected(true);
                                tab_Setup.setSelected(false);
                                page_Lock.setVisibility(View.VISIBLE);
                                page_Setup.setVisibility(View.GONE);
                                break;
                        }
                        break;
                    case R.id.tab_Setup:
                        switch (event.getAction())
                        {
                            case MotionEvent.ACTION_UP:
                                tab_Lock.setSelected(false);
                                tab_Setup.setSelected(true);
                                page_Lock.setVisibility(View.GONE);
                                page_Setup.setVisibility(View.VISIBLE);
                                break;
                        }
                        break;
                }
                return false;
            }
        };
        tab_Lock.setOnTouchListener(MenuListener);
        tab_Setup.setOnTouchListener(MenuListener);
        tab_Lock.setSelected(true);//디폴트로 Lock메뉴 선택
        //(End)메뉴 초기설정


        //(Start)Lock페이지 초기설정
        //<--자동잠금시스템-->
        if(GuardianInfo.getString("AutoLocking","0").equals("1"))
        {
            lock_AutoLocking.setChecked(true);
            Alarm_HeartBeat.setRepeating(AlarmManager.ELAPSED_REALTIME_WAKEUP, SystemClock.elapsedRealtime(), 5 * 1000, Alarm_sender);// 알람을 받을 시간을 5초 뒤로 설정
            lock_autoLockingText.setText("활성됨");
        }
        else
        {
            lock_AutoLocking.setChecked(false);
            lock_autoLockingText.setText("비 활성됨");
        }
        //<--자동잠금시스템 리스너-->
        lock_AutoLocking.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked)
                {
                    GuardianInfo_Editor.putString("AutoLocking", "1");
                    GuardianInfo_Editor.commit();
                    //AngelaInfo_Editor.apply();
                    Alarm_HeartBeat.setRepeating(AlarmManager.ELAPSED_REALTIME_WAKEUP, SystemClock.elapsedRealtime(), 1 * 1000, Alarm_sender);
                    lock_autoLockingText.setText("활성됨");
                    vibrator.vibrate(300);
                }
                else
                {
                    GuardianInfo_Editor.putString("AutoLocking", "0");
                    GuardianInfo_Editor.commit();
                    Alarm_HeartBeat.cancel(Alarm_sender);
                    lock_autoLockingText.setText("비 활성됨");
                    vibrator.vibrate(300);
                }
            }
        });

        lock_operatingLock.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP)
                {
                    SendMessage("TYPE=LOCK:ID="+IDEncrypt()+":");
                }
                return false;
            }
        });
        //(End)Lock페이지 초기설정

        //(Start)Setup페이지 초기설정
        //IP입력 텍스트박스 조건지정
        setup_TextIP.setText(GuardianInfo.getString("IP","192.168.0.2"));
        setup_TextIP.setFilters(new InputFilter[]{
                new InputFilter.LengthFilter(15),
                new InputFilter() {
                    @Override
                    public CharSequence filter(CharSequence source, int start, int end, Spanned dest, int dstart, int dend) {
                        Pattern ps = Pattern.compile("^[.0-9]*$");  //.문자와 0부터 9까지의 숫자만 입력 가능
                        if (!ps.matcher(source).matches())   //이 이외의 문자 입력시
                            return "";                      //빈문자가 입력되도록(아무것도 입력되지않음)
                        return null;
                    }
                }
        });
        //IP세팅
        setup_SaveIP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String TempIP = setup_TextIP.getText().toString();
                int ip[] = new int[4];
                for (int i = 0; i < 4; i++) {
                    ip[i] = Integer.parseInt(TempIP.split("[.]")[i]);
                    if (ip[i] < 0 || ip[i] > 255)    //IP가 0부터 255의 범위를 벗어날 경우
                    {
                        Toast.makeText(getApplicationContext(), "IP형식이 이상해요!", Toast.LENGTH_SHORT).show();
                        return;
                    }
                }

                int count = 0;
                for (int i = 0; i < TempIP.length(); i++)
                    if (TempIP.charAt(i) == '.') //IP의 .문자의 개수가 3개가 아닐 경우
                        count++;
                if (count != 3) {
                    Toast.makeText(getApplicationContext(), "IP형식이 이상해요!", Toast.LENGTH_SHORT).show();
                    return;
                }

                TempIP = ip[0] + "." + ip[1] + "." + ip[2] + "." + ip[3]; //ip앞에 0문자가 붙은 경우를 위해 숫자->문자 변환
                setup_TextIP.setText(TempIP);
                GuardianInfo_Editor.putString("IP", TempIP);
                GuardianInfo_Editor.commit();

                //IP재설정
                try {
                    ServerAddr = InetAddress.getByName(GuardianInfo.getString("IP", "192.168.0.2"));
                } catch (UnknownHostException e) {
                    e.printStackTrace();
                }
                vibrator.vibrate(500);
                Toast.makeText(getApplicationContext(), "저장했어요!", Toast.LENGTH_SHORT).show();
            }
        });

        //서버에 등록
        setup_Register.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                //(Start)키 생성
                //식별ID를 복호화할 키
                TempKey = new String();  //임시 키(서버에서 OK사인이 떨어지면 프리퍼런스에 저장)
                for(int i=0 ; i<16 ; i++)
                {
                    TempKey = TempKey + (int)(Math.random()*0xFF) + ",";
                }
                //키 전송을 위해 내장 키로 암호화
                byte[] byteKey = StrNumToByte(TempKey);
                byte[] encryptKey = KISA_SEED_CBC.SEED_CBC_Encrypt(EmbedKey, EmbedIV, byteKey, 0, byteKey.length);
                //(End)키 생성

                //(Start)ID생성
                //스마트폰 식별ID
                TempID = new String(); //임시 값(서버에서 OK사인이 떨어지면 프리퍼런스에 저장)
                for(int i=0 ; i<14 ; i++)
                {
                    TempID = TempID + (int)(Math.random()*0xFF) + ",";
                }
                //하위 2바이트에 타임스탬프 붙이기
                String TempIDAttached = attachTimeStamp(TempID);
                //(End)ID생성

                //위에서 생성한 키로 ID 암호화
                byte[] byteID = StrNumToByte(TempIDAttached);
                byte[] encryptID = KISA_SEED_CBC.SEED_CBC_Encrypt(byteKey, EmbedIV, byteID, 0, byteID.length);

                SendMessage("TYPE=REGI:PNUM=" + PhoneNumber + ":KEY=" + ByteToStrNum(encryptKey) + ":ID=" + ByteToStrNum(encryptID) + ":");
                Log.d("Fairy", "KEY"+ByteToStrNum(byteKey));
                Log.d("Fairy", "ID"+ByteToStrNum(byteID));
            }
        });
        //(End)Setup페이지 초기설정
    }
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


    @Override
    protected void onStart()    //앱 시작
    {
        SendMessage("TYPE=LINK:");
        super.onStart();
    }

    public void SendMessage(final String str)
    {
        new Thread(new Runnable()
        {
            public void run()
            {
                try
                {
                    byte[] buf = str.getBytes();
                    DatagramPacket packet = new DatagramPacket(buf, buf.length, ServerAddr, 8787);
                    UDPSocket.send(packet);
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    //UI핸들러
    class UIHandlerMessageQueue extends Handler {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what)
            {
                case UI_LOCK:
                    lock_operatingLock.setSelected(false);
                    break;
                case UI_UNLOCK:
                    lock_operatingLock.setSelected(true);
                    break;
            }
        }
    };
}
