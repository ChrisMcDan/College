package edu.shsu.mydialog;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity
{

    Button button;
    AlertDialog.Builder builder;
    View view;
    TextView title;
    ImageButton imageButton;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = (Button) findViewById(R.id.button);   //Draw button

        button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                builder = new AlertDialog.Builder(MainActivity.this);

                view = LayoutInflater.from(MainActivity.this).inflate(R.layout.custom_layout, null);

                title = (TextView) view.findViewById(R.id.title);
                imageButton = (ImageButton) view.findViewById(R.id.image);

                title.setText("HCI Class");

                imageButton.setImageResource(R.drawable.grad);

                builder.setPositiveButton("Yes, it was awesome!", new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        Toast.makeText(MainActivity.this, "Good Answer!", Toast.LENGTH_SHORT).show();
                    }
                });

                builder.setNegativeButton("No, it was terrible.", new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        Toast.makeText(MainActivity.this, "Wrong Answer!", Toast.LENGTH_SHORT).show();
                    }
                });

                builder.setView(view);
                builder.show();
            }
        });
    }
}
