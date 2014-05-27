function[effints] = test123(EEG)

tic
intervals = getintervals(EEG);

%effints = cell(EEG.nbchan, length(intervals));
effints = cell(length(EEG.data(1:length(EEG.icachansind),1,1)), length(intervals));
currentoffset = 0;
%loop for each event intervals
for i=1:length(intervals)
    %loop for each component in interval
    for j=1:length(intervals{i}(:,1))
        %EEGReaction algorithm
        effint = effectiveinterval(intervals{i}(j,:), currentoffset);
        effints{j,i} = effint;
        disp(['i = ',num2str(i),' j = ', num2str(j)])
    end
    currentoffset = currentoffset + length(intervals{i}(1,:));
end
%effectiveinterval(intervals{2}(2,:))
toc
