function[effinterval] = effectiveinterval(interval, timeinterval, offset)

record = calcnegentropy(interval);
leftrecord = 1;

rightrecord = length(interval);
max_right_value = rightrecord;
if and(timeinterval > 0, timeinterval < length(interval))
    rightrecord = timeinterval;
    max_right_value = timeinterval;
end

%brute-force search
%
%for i=1:length(interval)
%    for j=1:length(interval)-i
%        curinterval = interval(j:i);
%        result = calcnegentropy(curinterval);
%        if (result > record)
%            record = result;
%            leftrecord = j;
%            rightrecord = i;
%        end
%    end
%end

%Lazarenko's algorithm

stepdiv = 2;
step = rightrecord;
while (step > 1)
    step = fix(step / stepdiv);
    left = leftrecord;
    right = rightrecord;
    %left - step
    if (leftrecord > step )
        if (rightrecord - step > leftrecord - step )
            curinterval = interval(leftrecord - step : rightrecord - step);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord - step;
                right = rightrecord - step;   
            end 
        end
        
        if (rightrecord > leftrecord - step)
            curinterval = interval(leftrecord - step : rightrecord);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord - step;
                right = rightrecord;
            end
        end
        
        if ((rightrecord + step) <= max_right_value && rightrecord + step > leftrecord - step)
            curinterval = interval(leftrecord - step : rightrecord + step);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord - step;
                right = rightrecord + step;
            end 
        end
    end
    %left
    if ((rightrecord - step) > leftrecord)
        curinterval = interval(leftrecord : rightrecord - step);
        result = calcnegentropy(curinterval);
        if (result > record)
            record = result;
            left = leftrecord;
            right = rightrecord - step;
        end 
    end

    if ((rightrecord + step) <= max_right_value && rightrecord + step > leftrecord)
        curinterval = interval(leftrecord : rightrecord + step);
        result = calcnegentropy(curinterval);
        if (result > record)
            record = result;
            left = leftrecord;
            right = rightrecord + step;
        end 
    end
    %left + step
    if ((leftrecord + step) < max_right_value)
        if ((rightrecord - step) > (leftrecord + step)) 
            curinterval = interval(leftrecord + step : rightrecord - step);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord + step;
                right = rightrecord - step;
            end 
        end
        
        if (rightrecord > leftrecord + step)
            curinterval = interval(leftrecord + step : rightrecord);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord + step;
                right = rightrecord;
            end
        end
        
        if ((rightrecord + step) <= max_right_value && rightrecord + step > leftrecord + step)
            curinterval = interval(leftrecord + step : rightrecord + step);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord + step;
                right = rightrecord + step;
            end 
        end
    end
    
    if (right - left > 3)
        leftrecord = left;  
        rightrecord = right;
    end
   
end
effinterval = struct('negentropy', record, 'left', leftrecord, 'right', rightrecord, 'offset', offset);