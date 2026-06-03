% =========================================================================
% BANC DE TEST AUDIO - Simulation avant portage sur STM32
% =========================================================================
clear; clc; close all;

%% 1. Génération du signal d'entrée (Simulation du Microphone / ADC)
Fs = 48000;             % Fréquence d'échantillonnage (48 kHz)
t = 0:1/Fs:2;           % Vecteur temps pour une durée de 2 secondes
f_note = 440;           % Fréquence du signal : 440 Hz (Note La)

% Création d'une onde sinusoïdale pure (amplitude 0.2 pour laisser de la marge)
signal_brut = 0.2 * sin(2 * pi * f_note * t); 

%% 2. Paramètres de notre effet
gain_utilisateur = 8;   % On amplifie fort pour forcer la distorsion
seuil_clipping = 0.8;   % Seuil de saturation (Le maximum théorique est 1.0)

%% 3. Appel de la fonction de traitement (Celle qui ira dans le STM32)
% On fait passer le signal brut dans notre algorithme
signal_traite = effet_distorsion(signal_brut, gain_utilisateur, seuil_clipping);

%% 4. Écoute des résultats (Attention au volume de votre PC !)
disp('Écoute du signal brut (Son pur)...');
sound(signal_brut, Fs);
pause(2.5); % On attend que le son se termine

disp('Écoute du signal traité (Distorsion)...');
sound(signal_traite, Fs);

%% 5. Affichage à l'oscilloscope virtuel
figure('Name', 'Simulation DSP Audio', 'NumberTitle', 'off');

% On affiche seulement les 500 premiers échantillons pour bien voir la forme d'onde
nb_points = 500; 

% Graphique du haut : L'entrée
subplot(2,1,1);
plot(t(1:nb_points), signal_brut(1:nb_points), 'LineWidth', 1.5);
title('Signal Original (Ce qui rentre dans l''ADC)');
xlabel('Temps (s)'); ylabel('Amplitude');
ylim([-1.2 1.2]);
grid on;

% Graphique du bas : La sortie
subplot(2,1,2);
plot(t(1:nb_points), signal_traite(1:nb_points), 'r', 'LineWidth', 1.5);
title(['Signal Traité (Ce qui sort du DAC) - Gain: ', num2str(gain_utilisateur)]);
xlabel('Temps (s)'); ylabel('Amplitude');
ylim([-1.2 1.2]);
grid on;

