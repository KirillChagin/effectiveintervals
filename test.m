function[fulldata] = test(EEG)
fulldata = zeros(EEG.nbchan, EEG.pnts*EEG.trials);
for i=1:length(EEG.trials)
    fulldata = horzcat(fulldata, EEG.data(:,:,i));
end