function [ normal ] = normalToVectorXY( v1, v2, dir, normNormal, doPlot )
%NORMALTOTRAJ Computes the normal to a vector defined between two vectors
%v1 and v2. 
%   normal = normalToVectorXY( v1, v2, dir, normNormal, doPlot ) takes two input
%   vectors v1 and v2 and computes the XY normal vector to the one between
%   them (v2 - v1). If normNormal is one or not specified, it will return 
%   the unitary normal vector. Otherwise the norm of this orthogonal vector
%   will be normNormal. 
% 
%   normal = normalToVectorXY( v1, v2, 'left', normNormal, doPlot ) As before, but
%   the normal will be pointing towards the 'left' of the vector, as if you
%   were standing on the vector looking in its direction. See depiction
%   below.
%
%   normal = normalToVectorXY( v1, v2, 'right', normNormal, doPlot ) As before, but
%   the normal will be pointing towards the 'right' of the vector, as if you
%   were standing on the vector looking in its direction. See depiction
%   below.
%                                      
%                left                   /
%             ---------->        left  /  right
%                right                /
%

if (nargin < 5)
    doPlot = false;
end
if (nargin < 4)
    normNormal = 1;
end

if strcmp(dir, 'right')
    normal = (1/norm(v2 - v1)) * cross((v2 - v1), [0 0 1]');
else if strcmp(dir, 'left')
    normal = (1/norm(v2 - v1)) * cross([0 0 1]', (v2 - v1));
    else
        error('Valid directions are right and left. Try again')
    end
end

normal = normNormal*normal;

if (doPlot == true)
    arrow(v1, v1 + normal, 'Length', 4);
end

end

