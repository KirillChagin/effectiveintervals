function[effints] = calceffectiveintervals(EEG, eventtypes, timeinterval)

tic
intervals = getintervals(EEG);

%effints = cell(EEG.nbchan, length(intervals));
effints = cell(length(EEG.data(1:length(EEG.icachansind),1,1)), length(intervals));
currentoffset = 0;

%loop for each component of the first interval (before the first event)
for j=1:length(intervals{1}(:,1))
    %Empty interval for each component for the first interval
    effint = struct('negentropy', -1, 'left', 1, 'right', 1, 'offset', currentoffset);
    effints{j,1} = effint;
end
currentoffset = currentoffset + length(intervals{1}(1,:));
%loop for each event intervals
for i=2:length(intervals)
    %loop for each component in interval
    contains = ismember(EEG.event(i - 1).type, eventtypes);
    if (contains(1) == 1)
        for j=1:length(intervals{i}(:,1))
            %EEGReaction algorithm
            effint = effectiveinterval(intervals{i}(j,:), timeinterval, currentoffset);
            effints{j,i} = effint;
            disp(['i = ',num2str(i),' j = ', num2str(j)])
        end
    else
        for j=1:length(intervals{i}(:,1))
            %Empty interval for each component for unselected event
            effint = struct('negentropy', -1, 'left', 1, 'right', 1, 'offset', currentoffset);
            effints{j,i} = effint;
            disp(['skip i = ',num2str(i),' j = ', num2str(j)])
        end
    end
    currentoffset = currentoffset + length(intervals{i}(1,:));
end
%effectiveinterval(intervals{2}(2,:))
toc
