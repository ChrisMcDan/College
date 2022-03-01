package edu.shsu.lab1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class Lab1Activity extends AppCompatActivity
{

    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Bundle myInput = this.getIntent().getExtras();

        TextView t=new TextView(this);
        t=(TextView)findViewById(R.id.textView);
        t.setText("Hello " + (myInput.getString("username")));
    }
}
