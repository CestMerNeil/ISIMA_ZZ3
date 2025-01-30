//
//  CircleImage.swift
//  landmarks
//
//  Created by Ao XIE on 28/01/2025.
//

import SwiftUI


struct CircleImage: View {
    var image: Image
    
    var body: some View {
        image
            .clipShape(Circle())
            .overlay {
                Circle().stroke(.white, lineWidth: 4)
            }
            .shadow(radius: 7)
    }
}


#Preview {
    CircleImage(image: Image("turtlerock"))
}

