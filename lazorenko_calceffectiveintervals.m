function[effints] = lazorenko_calceffectiveintervals(EEG, eventtypes, timeinterval_left, timeinterval_right)

tic
intervals = lazarenko_getintervals(EEG);

effints = cell(EEG.nbchan, length(intervals));
currentoffset = 0;

intervalrate_right = round((timeinterval_right * EEG.srate) / 1000);
intervalrate_left = round((timeinterval_left * EEG.srate) / 1000);
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
    if isnumeric(EEG.event(i-1).type)
        contains = ismember(num2str(EEG.event(i-1).type), eventtypes);
    else
        contains = ismember(EEG.event(i - 1).type, eventtypes);
    end
    
    previous_interval_length = length(intervals{i-1}(1,:));
    
    if (contains(1) == 1)
        for j=1:length(intervals{i}(:,1))
            %getting a right part of previous interval for left limit
            if (intervalrate_left <= 0)
                %EEGReaction algorithm
                effint = effectiveinterval(intervals{i}(j,:), intervalrate_right, currentoffset);
                effints{j,i} = effint;
            elseif (previous_interval_length > intervalrate_left)
                timed_interval = cat(2, intervals{i-1}(j,end-intervalrate_left:end), intervals{i}(j,:)); 
                %EEGReaction algorithm
                effint = effectiveinterval(timed_interval, intervalrate_left + intervalrate_right, currentoffset - intervalrate_left);
                effints{j,i} = effint;
            else
                timed_interval = cat(2, intervals{i-1}(j,:), intervals{i}(j,:)); 
                %EEGReaction algorithm
                effint = effectiveinterval(timed_interval, previous_interval_length + intervalrate_right, currentoffset - previous_interval_length);
                effints{j,i} = effint;
            end
            
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
