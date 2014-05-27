function ploteffectiveintervals(EEG, effints)

effintssize = size(effints);
fullsize = effintssize(1) * effintssize(2);
winrej = zeros(fullsize, effintssize(1) + 5);
for i=1:effintssize(2)
    for j=1:effintssize(1)
        effint = effints{j,i};
        left = effint.offset + effint.left;
        right = effint.offset + effint.right;
        channels = zeros(1,effintssize(1));
        channels(j) = 1;
        ind = (i-1)*effintssize(2) + j;
        winrej(ind,1:5) = [left right 1 1 1];
        winrej(ind,6:end) = channels;
    end;
end;

icadata = (EEG.icaweights*EEG.icasphere)*EEG.data(EEG.icachansind,:);
eegplot(icadata, 'srate', EEG.srate, 'title', 'Scroll component activities -- eegplot()', ...
			 'limits', [EEG.xmin EEG.xmax]*1000,'winrej',winrej, 'events', EEG.event); 