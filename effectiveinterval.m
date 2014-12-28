function[effinterval] = effectiveinterval(interval, timeinterval, offset, constraint_left, constraint_right, superiority_coef, min_int_len)

record = calcnegentropy(interval);
relative_record = record;
leftrecord = 1;

rightrecord = length(interval);
max_right_value = rightrecord;

l_constr = 0;
r_constr = max_right_value;
sup_coef = superiority_coef;

if and(timeinterval > 0, timeinterval < length(interval))
    rightrecord = timeinterval;
    max_right_value = timeinterval;
end

if (constraint_left < constraint_right )
    if and(constraint_left > 0, constraint_right <  max_right_value)
        l_constr = constraint_left;
        r_constr = constraint_right;
    end 
end

if (sup_coef < 1)
    sup_coef = 1;
end

if or(l_constr ~= 0,  r_constr ~= max_right_value)
    relative_record = record / sup_coef;
end

if (min_int_len < 3)
    min_int_len = 3;
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
            if (result > relative_record)
                if and(leftrecord - step >= l_constr, rightrecord - step <= r_constr)
                    relative_record = result;
                else
                    relative_record = result / sup_coef;
                end
                record = result;
                left = leftrecord - step;
                right = rightrecord - step;   
            end 
        end
        
        if (rightrecord > leftrecord - step)
            curinterval = interval(leftrecord - step : rightrecord);
            result = calcnegentropy(curinterval);
            if (result > relative_record)
                if and(leftrecord - step >= l_constr, rightrecord <= r_constr)
                    relative_record = result;
                else
                    relative_record = result / sup_coef;
                end
                record = result;
                left = leftrecord - step;
                right = rightrecord;
            end
        end
        
        if ((rightrecord + step) <= max_right_value && rightrecord + step > leftrecord - step)
            curinterval = interval(leftrecord - step : rightrecord + step);
            result = calcnegentropy(curinterval);
            if (result > relative_record)
                if and(leftrecord - step >= l_constr, rightrecord + step <= r_constr)
                    relative_record = result;
                else
                    relative_record = result / sup_coef;
                end
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
        if (result > relative_record)
            if and(leftrecord >= l_constr, rightrecord - step <= r_constr)
                relative_record = result;
            else
                relative_record = result / sup_coef;
            end
            record = result;
            left = leftrecord;
            right = rightrecord - step;
        end 
    end

    if ((rightrecord + step) <= max_right_value && rightrecord + step > leftrecord)
        curinterval = interval(leftrecord : rightrecord + step);
        result = calcnegentropy(curinterval);
        if (result > relative_record)
            if and(leftrecord >= l_constr, rightrecord + step <= r_constr)
                relative_record = result;
            else
                relative_record = result / sup_coef;
            end
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
            if (result > relative_record)
                if and(leftrecord + step >= l_constr,  rightrecord - step <= r_constr)
                    relative_record = result;
                else
                    relative_record = result / sup_coef;
                end
                record = result;
                left = leftrecord + step;
                right = rightrecord - step;
            end 
        end
        
        if (rightrecord > leftrecord + step)
            curinterval = interval(leftrecord + step : rightrecord);
            result = calcnegentropy(curinterval);
            if (result > relative_record)
                if and(leftrecord + step >= l_constr,  rightrecord <= r_constr)
                    relative_record = result;
                else
                    relative_record = result / sup_coef;
                end
                record = result;
                left = leftrecord + step;
                right = rightrecord;
            end
        end
        
        if ((rightrecord + step) <= max_right_value && rightrecord + step > leftrecord + step)
            curinterval = interval(leftrecord + step : rightrecord + step);
            result = calcnegentropy(curinterval);
            if (result > relative_record)
                if and(leftrecord + step >= l_constr,  rightrecord + step <= r_constr)
                    relative_record = result;
                else
                    relative_record = result / sup_coef;
                end
                record = result;
                left = leftrecord + step;
                right = rightrecord + step;
            end 
        end
    end
    
    if (right - left > min_int_len)
        leftrecord = left;  
        rightrecord = right;
    end
   
end
effinterval = struct('negentropy', record, 'left', leftrecord, 'right', rightrecord, 'offset', offset);