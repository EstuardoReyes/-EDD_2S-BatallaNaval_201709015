 g = Digraph('unix', filename='AP_'+gramati.nombre+'.jpg')
        g.attr(rankdir='LR', size='8,5')
        g.node("",shape="plaintext",witdh="0.0001",height="0.0001")
        g.node("i",shape="circle")
        g.node("p",shape="circle")
        g.node("q",shape="circle",witdh="1",height="1")
        g.node("f",shape="doublecircle")
        g.edge("","i")
        g.edge("i","p",label="λ,λ;#")
        g.edge("p","q",label="λ,λ;"+gramati.inicial)
        aux1 = ''
        aux2 = ''
        produ = []
        for i in gramati.producciones:
            aux = ''
            t = 0
            for e in i:
                if t != 0:
                    aux = aux + i[e]
                t = t + 1
            aux1 = aux1 + "λ,"+i["no terminal"]+";"+aux +"\\n"
            dic = {"noterminal":i["no terminal"],"terminal":aux}
            produ.append(dic)
        for f in gramati.terminal:
            aux2 = aux2 +f+","+f+";λ \\n"
        g.edge("q","q",label=aux1)
        g.edge("q","q",label=aux2,tailport="s",headport="sw")
        g.edge("q","f",label="λ,#;λ")
        g.re