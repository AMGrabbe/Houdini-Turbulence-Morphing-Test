//point(<geometry>geometry, string attribute_name, int pointnumber)
vector npos = point(1, "P", @ptnum % npoints(1));// point position from second input, equivalent to @P fpr first input

vector min, max, nmin, nmax;
getbbox(0, min, max);
getbbox(0, nmin, nmax);

float gradrange = 100 * chf("morphing_grad_range");
float offset = fit(@P.y, max.y, min.x, 1, gradrange);
offset += rand(@P) * chi("rand_offset");

float noffset = fit(npos.y, nmax.y, nmin.x, 1, gradrange);
offset += rand(npos) * chi("rand_offset");

float f = fit(@Frame, offset, 
    100 + noffset - gradrange - chi("rand_offset"), 
    0.0, 
    1.0);
f = chramp("ramp", f);

vector center = getbbox_center(0);
vector ncenter = getbbox_center(1);

vector currentPos = @P;
vector ncurrentPos = @P;

//rotation
float angle = 3.1415926535897932384 * 2.0 * f * chi("rotation_cycle");
matrix mat = ident();
rotate(mat, angle, set(0,1,0));
@P *= mat;
npos *= mat;

// turbulence noise
float sinf = sin(f * 3.1415926535897932384);

float noiseval = (noise(@P + currentPos * 100.0) - 0.5);
vector dir = normalize(@P - center) * sinf * noiseval;

float nnoiseval = (noise(npos + ncurrentPos * 100.0) - 0.5);
vector ndir = normalize(npos - ncenter) * sinf * nnoiseval;

@P += dir;
npos += dir;

@P = lerp(@P, npos, f);