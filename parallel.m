function [out] = parallel(array)
sum = 0;
for i = 1:length(array)
    ri = array(i);
    sum = sum + 1/ri;
out = 1/sum;
end

