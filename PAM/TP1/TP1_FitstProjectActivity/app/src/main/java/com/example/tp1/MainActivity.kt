package com.example.tp1

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.provider.MediaStore
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.tp1.ui.theme.TP1Theme
import com.example.tp1.ui.theme.Pink40

import androidx.activity.compose.rememberLauncherForActivityResult


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            TP1Theme {
                TP1_Activity1()
            }
        }
    }
}

@Composable
fun TP1_Activity1() {
    val message = remember { mutableStateOf("") }
    val context = LocalContext.current
    val takePictureIntent = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
    val launcher = rememberLauncherForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
        if (result.resultCode == Activity.RESULT_OK) {
            // Handle the result
        }
    }

    Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Button(onClick = {
                Toast.makeText(context, "Never use Android! PLEASE!", Toast.LENGTH_SHORT).show()
                message.value = "Android"
                launcher.launch(takePictureIntent)
            }, colors = ButtonDefaults.buttonColors(containerColor = Pink40)) {
                Text("Click me!")
            }
            if (message.value.isNotEmpty()) {
                Greeting(message.value)
            }
            TextField(
                value = message.value,
                onValueChange = { message.value = it },
                label = { Text("Enter your name") }
            )
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Never use Android! PLEASE! $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    TP1Theme {
        Greeting("Android", Modifier.padding(16.dp))
    }
}