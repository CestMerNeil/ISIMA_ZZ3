package com.example.tp1_compose.ui.compose

import androidx.compose.runtime.Composable
import org.jetbrains.annotations.TestOnly
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Text
import androidx.compose.material3.Button

@Composable
fun Alert(
    title: String,
    content: String,
    onConfirm: () -> Unit,
    onDismiss: () -> Unit
) {
    AlertDialog(
        onDismissRequest = onDismiss,
        title = {
            Text(text = title)
        },
        text = {
            Text(text = content)
        },
        dismissButton = {
            Button(onClick = onDismiss) {
                Text(text = "Cancel")
            }
        },
        confirmButton = {
            Button(onClick = onConfirm) {
                Text(text = "OK")
            }
        }
    )
}