function[effints] = calceffectiveintervals_ersp_max(EEG, eventtypes, timeinterval_left, timeinterval_right, constraint_left, constraint_right, superiority_coef, min_int_len)

intervals = getintervals(EEG);

%effints = cell(EEG.nbchan, length(intervals));
effints = cell(length(EEG.data(1:length(EEG.icachansind),1,1)), length(intervals));
currentoffset = 0;

intervalrate_right = round((timeinterval_right * EEG.srate) / 1000);
intervalrate_left = round((timeinterval_left * EEG.srate) / 1000);
constraintrate_right = round((constraint_right * EEG.srate) / 1000);
constraintrate_left = round((constraint_left * EEG.srate) / 1000);
min_int_len_rate = round((min_int_len * EEG.srate) / 1000);
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
            %constructing timed_interval
            timed_interval = intervals{i}(j,:);
            timeinterval_param = intervalrate_right;
            offset_param = currentoffset;
            
            %getting a right part of previous interval for left limit
            if (intervalrate_left <= 0)
                timed_interval = intervals{i}(j,:);
                timeinterval_param = intervalrate_right;
                offset_param = currentoffset; 
            elseif (previous_interval_length > intervalrate_left)
                timed_interval = cat(2, intervals{i-1}(j,end-intervalrate_left:end), intervals{i}(j,:)); 
                timeinterval_param = intervalrate_left + intervalrate_right;
                offset_param = currentoffset - intervalrate_left; 
            else
                timed_interval = cat(2, intervals{i-1}(j,:), intervals{i}(j,:));
                timeinterval_param = previous_interval_length + intervalrate_right;
                offset_param = currentoffset - previous_interval_length; 
            end
            
            %add right interval if right bound is greater than interval lenght
            if and(length(intervals{i}(j,:)) < intervalrate_right, i < length(intervals))
                if (length(intervals{i}(j,:)) +  length(intervals{i+1}(j,:)) > intervalrate_right)
                    timed_interval = cat(2, timed_interval, intervals{i+1}(j,1:intervalrate_right-length(intervals{i}(j,:))));
                else
                    timed_interval = cat(2, timed_interval, intervals{i+1}(j,:));
                end
            end

            %%% Calculate ERSP and get effective interval with max
            %%% negentropy for all freqs
            tlimits = [0 length(timed_interval)];
            cycles = [3 0.5];
            options = [];
            options = [ options ', ''plotersp'',  ''off'',  ''plotitc'',  ''off'', ''plotphasesign'',  ''off'', ''baseline'', [0], ''plotphase'', ''off'', ''padratio'', [1], ''timesout'', -1' ];
            
            com = sprintf('newtimef(timed_interval, length(timed_interval), [tlimits(1) tlimits(2)], EEG.srate, cycles %s);', options);
            [eval_out, ersp,itc,powbase,times,freqs,erspboot,itcboot] = evalc(com);
         
            ersp_size = size(ersp);
            nfreqs = ersp_size(1);
            timesout = ersp_size(2);
            
            max_left = 1;
            max_right = 1;
            max_negentropy = 0;
            
            %%% Calculate right border in ms and then convert it to array
            %%% index. Needed coz ersp times are not equal to array length
            ersp_timeinterval_param = timesout;
            ersp_timeinterval_ms = times(end);
            closest_record = ersp_timeinterval_ms;
            
            
            if timeinterval_left <= 0
                ersp_timeinterval_ms = timeinterval_right;
            else
                ersp_timeinterval_ms = timeinterval_left + timeinterval_right;
            end
            
            if ersp_timeinterval_ms > times(1) && ersp_timeinterval_ms < times(end)
                for t=1:length(times)
                    if abs(times(t) - ersp_timeinterval_ms) <= closest_record
                        closest_record = abs(times(t) - ersp_timeinterval_ms);
                        ersp_timeinterval_param = t;
                    end
                end
            end
            
            for f=1:nfreqs
                %%% Calculates without constraints
                neg_effint = effectiveinterval(ersp(f,:), ersp_timeinterval_param, offset_param, 0, ersp_timeinterval_param, 1, min_int_len_rate);
                
                if neg_effint.negentropy > max_negentropy
                    max_left = neg_effint.left;
                    max_right = neg_effint.right;
                    max_negentropy = neg_effint.negentropy;
                end
            end

            %%% Get times back to array indexes
            effint_left = round((times(max_left) * EEG.srate) / 1000);
            effint_right = round((times(max_right) * EEG.srate) / 1000);
            
            %%% ----------------------------------------------------------
            effint = struct('negentropy', max_negentropy, 'left', effint_left, 'right', effint_right, 'offset', offset_param);
            effints{j,i} = effint;
            disp(['i = ',num2str(i),' j = ', num2str(j), ' ersp_int_ms = ', num2str(ersp_timeinterval_ms), ' ersp_int_param = ', num2str(ersp_timeinterval_param), ' max_right = ', num2str(max_right), ' effint_right = ', num2str(effint_right)])
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
