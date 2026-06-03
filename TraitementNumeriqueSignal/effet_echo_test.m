
clear; clc; close all;


Fs = 12000; 


t_bip = 0:1/Fs:0.2;           
bip = 0.5 * sin(2*pi*880*t_bip); 

t_silence = 0:1/Fs:2;        
silence = zeros(1, length(t_silence));

signal_entree = [bip, silence]'; 
nb_echantillons = length(signal_entree);


retard_ms = 500;   
gain_echo = 0.6;   


retard_echantillons = round((retard_ms / 1000) * Fs);


if retard_echantillons > 10000
    error('Erreur : Délai trop long, la RAM de votre STM32 va saturer !');
end

signal_sortie = zeros(nb_echantillons, 1);
clear effet_echo; 
disp('Traitement de l''audio en cours (échantillon par échantillon)...');
for i = 1:nb_echantillons
    
    signal_sortie(i) = effet_echo(signal_entree(i), gain_echo, retard_echantillons);
end

disp('Écoute du son original...');
sound(signal_entree, Fs);
pause(2.5);

disp('Écoute de l''écho (Style Lo-Fi 12 kHz)...');
sound(signal_sortie, Fs);

figure('Name', 'Simulation Buffer Circulaire');
plot(signal_entree, 'b'); hold on;
plot(signal_sortie, 'r', 'LineWidth', 1.2);
title(['Écho Numérique - Mémoire : ', num2str(retard_echantillons), ' cases utilisées sur 10000']);
xlabel('Temps (Nombre d''échantillons)');
ylabel('Amplitude');
legend('Son Original', 'Sortie avec Écho Feedback');
grid on;