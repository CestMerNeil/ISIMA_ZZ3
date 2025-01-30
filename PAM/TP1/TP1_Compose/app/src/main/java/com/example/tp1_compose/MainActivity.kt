package com.example.tp1_compose

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.tp1_compose.ui.theme.TP1_ComposeTheme
import androidx.compose.runtime.mutableStateOf

import com.example.tp1_compose.ui.compose.Alert
import com.example.tp1_compose.ui.compose.CatCard
import androidx.compose.material3.Button

import androidx.compose.foundation.layout.Box
import androidx.compose.ui.Alignment


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            val showAlert = remember { mutableStateOf(false) }

            TP1_ComposeTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Box(
                        modifier = Modifier
                            .fillMaxSize()
                            .padding(innerPadding),
                        contentAlignment = Alignment.Center
                    ) {
                        val jsonString = """
                            [
                                {
                                    "_id": "tyU23CXdkKSFghVc",
                                    "mimetype": "image/png",
                                    "size": 51395,
                                    "tags": [
                                        "cute"
                                    ]
                                },
                                {
                                    "_id": "GUOunrpLPB6Jw0zE",
                                    "mimetype": "image/jpeg",
                                    "size": 37933,
                                    "tags": [
                                        "handicapped",
                                        "tabby",
                                        "double",
                                        "multiple"
                                    ]
                                },
                                {
                                    "_id": "dmjubveyQIbCFA2v",
                                    "mimetype": "image/jpeg",
                                    "size": 29927,
                                    "tags": [
                                        "orange"
                                    ]
                                },
                                {
                                    "_id": "UIx85TPiQmqwFOBL",
                                    "mimetype": "image/jpeg",
                                    "size": 45668,
                                    "tags": [
                                        "cute"
                                    ]
                                },
                                {
                                    "_id": "6SOOsD3JbXiiTDqI",
                                    "mimetype": "image/jpeg",
                                    "size": 9462,
                                    "tags": [
                                        "cute"
                                    ]
                                },
                                {
                                    "_id": "rlvjW7s7QChiFKF6",
                                    "mimetype": "image/jpeg",
                                    "size": 42175,
                                    "tags": [
                                        "cute"
                                    ]
                                },
                                {
                                    "_id": "e1PaGDQ92o1kBgNx",
                                    "mimetype": "image/jpeg",
                                    "size": 64335,
                                    "tags": [
                                        "cute",
                                        "orange"
                                    ]
                                },
                                {
                                    "_id": "iYlyC0d0iqmLqzeo",
                                    "mimetype": "image/jpeg",
                                    "size": 16669,
                                    "tags": [
                                        "cute"
                                    ]
                                },
                                {
                                    "_id": "oHmMzWNIx5A5ZRyV",
                                    "mimetype": "image/png",
                                    "size": 56868,
                                    "tags": [
                                        "dumb"
                                    ]
                                },
                                {
                                    "_id": "Ef4WWYRUi6qSSo0x",
                                    "mimetype": "image/jpeg",
                                    "size": 27042,
                                    "tags": [
                                        "catstickerss"
                                    ]
                                }
                            ]
                        """
                        if (showAlert.value) {
                            Alert(
                                title = "Title",
                                content = "Content",
                                onConfirm = {},
                                onDismiss = { showAlert.value = false }
                            )
                        }
                        CatCard(jsonString = jsonString)
                        Button(
                            onClick = { showAlert.value = true }
                        ) {
                            Text("Show Alert")
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    TP1_ComposeTheme {
        Greeting("Android")
    }
}