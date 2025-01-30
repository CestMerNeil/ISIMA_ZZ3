package com.ao_xie.yolo_kotlin.ui.components

import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Api
import androidx.compose.material.icons.filled.FlashOn
import androidx.compose.material.icons.filled.Menu
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.compose.material.IconButton
import androidx.compose.material.Text

@Composable
fun TopBar(
    refreshRate: String,
    onMenuClick: () -> Unit,
    onFlashToggle: (Boolean) -> Unit,
    onApiToggle: (Boolean) -> Unit
) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp),
        horizontalArrangement = Arrangement.SpaceBetween,
        verticalAlignment = Alignment.CenterVertically
    ) {
        // 左侧信息栏
        Text(text = "Refresh Rate: $refreshRate", style = MaterialTheme.typography.body1)

        // 右侧控制栏
        Row(verticalAlignment = Alignment.CenterVertically) {
            IconButton(onClick = onMenuClick) {
                Icon(Icons.Default.Menu, contentDescription = "Open Menu")
            }
            IconButton(onClick = { onFlashToggle(true) }) {
                Icon(Icons.Default.FlashOn, contentDescription = "Flash On")
            }
            IconButton(onClick = { onApiToggle(true) }) {
                Icon(Icons.Default.Api, contentDescription = "OpenAI API On")
            }
        }
    }
}