function[intervals] = getintervals(EEG)

%fulldata = [;];
%for i=1:length(EEG.epoch)
%    fulldata = horzcat(fulldata, EEG.data(:,:,i));
%end

%icadata = EEG.icaweights * fulldata;

icadata = (EEG.icaweights*EEG.icasphere)*EEG.data(EEG.icachansind,:);

%intervals{1} = icadata(1:EEG.nbchan, 1 : EEG.event(1).latency - 1);
intervals{1} = icadata(1:length(EEG.data(1:length(EEG.icachansind),1,1)), 1 : EEG.event(1).latency - 1);
for i=1:length(EEG.event) - 1
    startcolumn = EEG.event(i).latency;
    endcolumn = EEG.event(i+1).latency - 1;
%    intervals{i + 1} = icadata(1:EEG.nbchan, startcolumn : endcolumn);
    intervals{i + 1} = icadata(1:length(EEG.data(1:length(EEG.icachansind),1,1)), startcolumn : endcolumn);
end;

startcolumn = EEG.event(length(EEG.event)).latency;
endcolumn = length(icadata(1,:));
%lastevent = icadata(1:EEG.nbchan, startcolumn : endcolumn);
lastevent = icadata(1:length(EEG.data(1:length(EEG.icachansind),1,1)), startcolumn : endcolumn);
intervals{length(EEG.event) + 1} = lastevent;

