function[chanNames] = getallchannelnames(EEG)
    tempNames = {};
    for i=1:length(EEG.chanlocs)
        tempNames{i} = EEG.chanlocs(i).labels;
    end;
    
    chanNames = tempNames;
end

    