package com.example.tp1_compose.ui.compose

import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable

@Serializable
data class Cat(
    @SerialName("_id") val id: String,
    val mimetype: String,
    val size: Int,
    val tags: List<String>
)