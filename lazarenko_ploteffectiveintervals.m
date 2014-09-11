function lazarenko_ploteffectiveintervals(EEG, effints, chantypes)

effintssize = size(effints);
fullsize = effintssize(1) * effintssize(2);
winrej = zeros(fullsize, effintssize(1) + 5);
for i=1:effintssize(2)
    for j=1:effintssize(1)
        if (any(chantypes == j))
            effint = effints{j,i};
            left = effint.offset + effint.left;
            right = effint.offset + effint.right;
            channels = zeros(1,effintssize(1));
            channels(j) = 1;
            ind = (i-1)*effintssize(2) + j;
            winrej(ind,1:5) = [left right 1 1 1];
            winrej(ind,6:end) = channels;
        end
    end;
end;

pop_eegplot_wrapper( EEG, 1, 1, 1, 1, 'winrej', winrej);