def CreatediffVarsVector():

    Vars = []

    Vars.append( "pt"       )
    Vars.append( "cts"      )
#    Vars.append( "ct1"      )
#    Vars.append( "ct2"      )
    Vars.append( "y"        )
    Vars.append( "m12"      )
    Vars.append( "m34"      )
    #Vars.append( "phi1"     )
    #Vars.append( "phi2"     )
    Vars.append( "njet"     )
    #Vars.append( "njetv2"   )
    #Vars.append( "njetv3"   )
    Vars.append( "nbjet"    )
    Vars.append( "ljpt"     )
    Vars.append( "mjj"      )
    Vars.append( "etajj"    )
    Vars.append( "phijj"    )
    Vars.append( "ptnjet"   )
    #Vars.append( "pty"      )
    Vars.append( "m12m34"   )
    #Vars.append( "FidChan"  )

    return Vars

def CreatediffChVector(v):

    Ch = []
    
    Ch.append( "incl"      )
    #Ch.append( "4mu"      )
    #Ch.append( "4e"       )
    #Ch.append( "2mu2e"    )
    #Ch.append( "2e2mu "    )
    if v == "m12" or v =="m34" or v=="m12m34":
      Ch.append( "2l2l"     )
      Ch.append( "4l"       )
   
    return Ch

def CreatedfloatqqZZVector():

    v = []
    
    v.append( "floatZZ"     )
    v.append( "fixZZ"      )

    return v

def CreateMatrixVector():

    v = []
    
    v.append( "cf"               )
    v.append( "matrix"      )

    return v

def CreateLepTypeVector():

    v = []
    
    v.append( ""          )
    #v.append( "Dres"      )
    #v.append( "Born"      )

    return v

def CreateSysVector():

    v = []
    
    v.append( ""                 )
    v.append( "_wsys"      )

    return v

def writeslide(f,v, c, qq, u, l, s):
    f.write("\\begin{frame}\n")
    title="\\frametitle{"+v+" "+c+" "+qq+" "+u+" "+l+" $"+s+" $ }\n"
    f.write(title)
    slide=str("\includegraphics[width=9cm]{../../ws_output/"+v+"/"+l+"/"+c+"/"+u+"/"+qq+"/fit_"+v+"_"+s+".eps}\n")
#    f.write(str("\includegraphics[width=9cm]{../../ws_output/"+v+"/"+l+"/"+c+"/"+u+"/"+qq+"/fit_"+v+"_"+s+".eps}\n"))
    f.write(slide)
    f.write("\end{frame}\n")
    f.write("\clearpage\n")


f = open("slides1.tex", "w")
  
f.write("\documentclass[9pt, compress]{beamer}\n")
f.write("\usepackage{booktabs}\n")
f.write("\\author{\\textbf{Rania Sayed}, \\textbf{Hazem Al Saied} }\n")
f.write("\\title{The research system in Germany}\n")
f.write("\institute{\\textbf{Uinversit de Lorraine}}\n")
f.write("\\begin{document}\n")
f.write("        \maketitle\n")

var = CreatediffVarsVector();
qqZZ= CreatedfloatqqZZVector();
unf = CreateMatrixVector();
lep = CreateLepTypeVector();
sys = CreateSysVector();

#Create the list of input commands
for v in var:
  ch  = CreatediffChVector(v);
  for c in ch:
    for qq in qqZZ:
      for u in unf:
        for l in lep:
	  for s in sys:
   	    writeslide(f,v,c,qq,u,l,s)


f.write("\\end{document}\n")
########################################################################################


