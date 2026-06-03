function signal_out = effet_echo(signal_in, gain_echo, retard_echantillons)
    persistent buffer_circulaire;
    persistent index_ecriture;
    
    taille_max = 10000; 
    
    if isempty(buffer_circulaire)
        buffer_circulaire = zeros(taille_max, 1); 
        index_ecriture = 1;
    end
    
   
    index_lecture = mod((index_ecriture - 1) - retard_echantillons + taille_max, taille_max) + 1;
    
    echantillon_passe = buffer_circulaire(index_lecture);
    
    signal_out = signal_in + (echantillon_passe * gain_echo);
    

    buffer_circulaire(index_ecriture) = signal_out;
    
    index_ecriture = mod(index_ecriture, taille_max) + 1;
end