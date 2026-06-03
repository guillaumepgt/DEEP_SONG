function signal_out = effet_distorsion(signal_in, gain, seuil)
    % EFFET_DISTORSION : Applique un effet de saturation (Hard Clipping)
    % signal_in : Tableau des échantillons provenant de l'ADC
    % gain      : Facteur de multiplication du volume
    % seuil     : Valeur maximale autorisée (pour simuler la limite matérielle)
    
    % 1. On amplifie le signal d'entrée
    amplifie = signal_in * gain;
    
    % 2. Écrêtage (Hard Clipping)
    % Tout ce qui dépasse le seuil positif est bloqué au seuil
    amplifie(amplifie > seuil) = seuil;
    
    % Tout ce qui dépasse le seuil négatif est bloqué au seuil négatif
    amplifie(amplifie < -seuil) = -seuil;
    
    % 3. On renvoie le signal traité vers le DAC
    signal_out = amplifie;
end