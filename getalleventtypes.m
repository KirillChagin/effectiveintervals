function[eventTypes] = getalleventtypes(EEG)
    tempTypes = {};
    for i=1:length(EEG.event)
        currentType = {EEG.event(i).type};
        contains = ismember(currentType, tempTypes);
        if contains(1) == 0
            tempTypes(length(tempTypes)+1) = currentType(1);
        end;
    end;
    
    eventTypes = tempTypes;
end

    