package com.example.david.smarth;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;


import java.io.IOException;
import java.util.concurrent.TimeUnit;

public class display_image extends AppCompatActivity {


    boolean flag = true;
    private boolean IsBase64Encoded(String value)
    {
        try {
            byte[] decodedString = Base64.decode(value, Base64.DEFAULT);
            BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_image);
        flag = true;

        final Handler RefreshHandler;
        RefreshHandler = new Handler() {

            @Override
            public void handleMessage(Message msg) {
                String imag= (String)msg.obj;
                if(imag != null && imag.length()>100 && IsBase64Encoded(imag) ) {


                    byte[] decodedString = Base64.decode(imag, Base64.DEFAULT);
                    final Bitmap decodedByte = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
                    ImageView image = (ImageView) findViewById(R.id.img1);
                    image.setImageBitmap(Bitmap.createScaledBitmap(decodedByte, 320, 270, false));


                }








            }

        };

        new Thread(new Runnable(){
            public void run(){
                //open socket

                Client client = new Client(new config().gethostname(), 22000);




                try {
                    client.connect();
                    client.readResponse();
                    while(true && flag ==true) {
                        client.sendDataForImage();
                        String img = client.readResponse();
                        System.out.println("imagen>  " + img);

                        String message = img;
                        Message msg = Message.obtain(); // Creates an new Message instance
                        msg.obj = message; // Put the string into Message, into "obj" field.
                        msg.setTarget(RefreshHandler); // Set the Handler
                        msg.sendToTarget();

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {

                                ;
                                final Button button = findViewById(R.id.button_back);
                                button.setOnClickListener(new View.OnClickListener() {
                                    public void onClick(View v) {
                                        display_image.this.finish();
                                        Intent intent = new Intent(display_image.this, main.class);
                                        display_image.this.startActivity(intent);
                                        flag = false;

                                    }
                                });
                            }
                        });
                        try {
                            TimeUnit.MILLISECONDS.sleep(400);
                        } catch (InterruptedException e) {
                            Intent intent = new Intent(display_image.this, display_image.class);
                            display_image.this.startActivity(intent);
                            display_image.this.finish();
                        }
                    }



                } catch (IOException e) {
                    Intent intent = new Intent(display_image.this, display_image.class);
                    display_image.this.startActivity(intent);
                    display_image.this.finish();
                }


            }
        }).start();



    }
}
