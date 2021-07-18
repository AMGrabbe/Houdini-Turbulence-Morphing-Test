vector min, max;
getbbox(0, min, max);

float gradrange = 100 * chf("morphing_grad_range");
float offset = fit(@P.y, max.y, min.x, 1, gradrange);
offset += rand(@P) * chi("rand_offset");

float f = fit(@Frame, offset, 100 + offset - gradrange - chi("rand_offset"), 0.0, 1.0);

vector center = getbbox_center(0);

vector pos = @P;
pos.y = center.y;
float dist = distance(pos, center);

float angle = 3.1415926535897932384 * 2.0 * f * chi("rotation_cycle");
matrix mat = ident();
rotate(mat, angle, set(0,1,0));
@P *= mat;
