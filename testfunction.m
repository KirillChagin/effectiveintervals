function[winrej] = testfunction(EEG)
epoch = [2,6,8];
epochchanind = {[2,4,6],[3,9,12],[6:12,16,18]};

rejepochcol =  [.95, .95, .95];
rejepoch = zeros(1,EEG.trials);
rejepoch(epoch) = ones(1,length(epoch));
rejepochE = zeros(EEG.nbchan,EEG.trials);
for i=1:length(find(rejepoch));
    rejepochE(epochchanind{i},epoch(i))=ones(size(epochchanind{i}));
end
rejepoch
rejepochE
winrej=trial2eegplot(rejepoch,rejepochE,EEG.pnts,rejepochcol);
