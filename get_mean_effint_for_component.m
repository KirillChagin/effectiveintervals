function[mean_effint] = get_mean_effint_for_component(EEG, EFFINTS, comp_num, event_types)
%%% Calculating of the mean value of right and left border of effective
%%% intervals for selected component
    
    effints_for_comp = EFFINTS(comp_num,:);
    
    lefts = NaN(1,length(effints_for_comp));
    rights = NaN(1,length(effints_for_comp));
    
    for i=1:length(effints_for_comp)
        if isnumeric(effints_for_comp{i}.event)
            contains = ismember(num2str(effints_for_comp{i}.event), event_types);
        else
            contains = ismember(effints_for_comp{i}.event, event_types);
        end
        
        if (~isempty(contains) && contains(1) == 1)
            if (~(effints_for_comp{i}.left == 1 && effints_for_comp{i}.right == 1) && effints_for_comp{i}.right - effints_for_comp{i}.left > 20)
                lefts(i) = mod(effints_for_comp{i}.offset + effints_for_comp{i}.left, EEG.pnts);
                rights(i) = lefts(i) + (effints_for_comp{i}.right - effints_for_comp{i}.left);
            end
        end
    end

    min_lefts = min(lefts);
    max_rights = max(rights);
    
    filtered_lefts = lefts(lefts > min_lefts + 10);
    filtered_rights = rights(rights < max_rights - 10);
    
    left = nanmean(filtered_lefts) + EEG.xmin * EEG.srate;
    right = nanmean(filtered_rights) + EEG.xmin * EEG.srate;
    
    mean_effint = struct('left', round(left), 'right', round(right));
end

    