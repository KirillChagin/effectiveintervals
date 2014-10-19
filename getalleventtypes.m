function[eventTypes] = getalleventtypes(EEG)
    tempTypes = {};
    for i=1:length(EEG.event)
        if isnumeric(EEG.event(i).type)
            currentType = {num2str(EEG.event(i).type)};
        else
            currentType = {EEG.event(i).type};
        end
        contains = ismember(currentType, tempTypes);
        if contains(1) == 0
            tempTypes(length(tempTypes)+1) = currentType(1);
        end;
    end;
    
    eventTypes = tempTypes;
end

    