#pragma once

template <typename Objet>
class Activateur
{
public:    
    Activateur(Objet o, unsigned nombreUtilisation = 0)
    {
        for (unsigned i = 0; i < nombreUtilisation; ++i)
        {
            o.activer();
        }
    }
};