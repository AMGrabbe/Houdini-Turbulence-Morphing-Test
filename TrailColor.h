int pts[] = primpoints(0, @primnum);

for(int i=0; i<len(pts); i++){
    //set up a color node with Color Type "Ramp from Attribute" and Attribute name: "u"
    setpointattrib(0, "u", pts[i], i/ float(len(pts)-1.0));
}