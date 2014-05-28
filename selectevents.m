function[chanlist] = selectevents(eventTypes, varargin)
    g = finputcheck(varargin, { 'withindex'     {  'integer';'string' } { [] {'on' 'off'} }   'off';
                            'select'        { 'cell';'string';'integer' } [] [];
                            'selectionmode' 'string' { 'single';'multiple' } 'multiple'});
    [chanlist,tmp,chanliststr] = listdlg2('PromptString', strvcat('(use shift|Ctrl to', 'select several)'), ...
            'ListString', eventTypes, 'initialvalue', g.select, 'selectionmode', g.selectionmode);     
end