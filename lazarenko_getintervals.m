function[intervals] = lazarenko_getintervals(EEG)

fulldata = reshape(EEG.data, EEG.nbchan, EEG.pnts*EEG.trials);

intervals{1} = fulldata(:, 1:EEG.event(1).latency - 1);
for i=1:length(EEG.event) - 1
    startcolumn = EEG.event(i).latency;
    endcolumn = EEG.event(i+1).latency - 1;
    intervals{i + 1} = fulldata(1:EEG.nbchan, startcolumn : endcolumn);
end;

startcolumn = EEG.event(length(EEG.event)).latency;
endcolumn = length(fulldata(1,:));
lastevent = fulldata(:, startcolumn : endcolumn);
intervals{length(EEG.event) + 1} = lastevent;

