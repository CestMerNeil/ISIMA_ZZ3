//
//  PokemonImage.swift
//  Pokemon
//
//  Created by Ao XIE on 11/02/2025.
//

import SwiftUI

struct PokemonImage: View {
    var image: Image
    
    var body: some View {
        image
            //.resizable()
            .aspectRatio(1, contentMode: .fill)
            .clipShape(Rectangle())
            .overlay {
                Rectangle().stroke(Color.white, lineWidth: 4)
            }
            .shadow(radius: 7)
    }
}

#Preview {
    PokemonImage(image: Image("254-Mega"))
}
