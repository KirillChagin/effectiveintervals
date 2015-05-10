function[mean_effint] = get_mean_effint_for_component(EEG, EFFINTS, comp_num, event_types)
%%% Calculating of the mean value of right and left border of effective
%%% intervals for selected component
    
    effints_for_comp = EFFINTS(comp_num,:);
    
    lefts = zeros(1,length(effints_for_comp));
    rights = zeros(1,length(effints_for_comp));
    
    for i=1:length(effints_for_comp)
        if isnumeric(effints_for_comp{i}.event)
            contains = ismember(num2str(effints_for_comp{i}.event), event_types);
        else
            contains = ismember(effints_for_comp{i}.event, event_types);
        end
        
        if (~isempty(contains) && contains(1) == 1)
            if (~(effints_for_comp{i}.left == 1 && effints_for_comp{i}.right == 1))
            lefts(i) = mod(effints_for_comp{i}.offset + effints_for_comp{i}.left, EEG.pnts);
            rights(i) = lefts(i) + (effints_for_comp{i}.right - effints_for_comp{i}.left);
            end
        end
    end
    
    filtered_lefts = nonzeros(lefts);
    filtered_rights = nonzeros(rights);
    
    left = mean(filtered_lefts) + EEG.xmin * EEG.srate;
    right = mean(filtered_rights) + EEG.xmin * EEG.srate;
    
    mean_effint = struct('left', round(left), 'right', round(right));
end

    