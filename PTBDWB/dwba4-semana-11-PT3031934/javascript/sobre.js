const {createElement} = React;
    const raiz = ReactDOM.createRoot(document.getElementById("raiz"));

    const conteudo = createElement('div', null,
        createElement('p',null,'O ',
            createElement('strong',null,'Instituto Federal de São Paulo'),
        ' - é uma autarquia federal de ensino.'),
        createElement('p',null,'Fundada em 1909, como Escola de Apredizes Artifíces, é reconhecida pela sociedade paulista por sua excelência no ensino público gratuito de qualidade.'),
        createElement('p',null,'Durante sua história, recebeu, também, os nomes de Escola Técnica Federal de São Paulo e Centro Federal de Educação Tecnológica de São Paulo. Com a transformação em Instituto, em dezembro de 2008, passou a ter relevância de universidade, destacando-se pela autonomia.'),
        createElement('p',null,'Com a mudança, o Instituto Federal de São Paulo passou a destinar 50% das vagas para os cursos técnicos e, no mínimo, 20% das vagas para os cursos de licenciatura, sobretudo nas áreas de Ciências e da Matemática. Completamente, continuará oferecendo cursos de formação inicial e continuada, tecnologias, engenharias e pós-graduação.'),
        createElement('p',null,'Além dos cursos presenciais, o Instituto Federal de São Paulo oferece os cursos Técnicos em Administração e em Informática para Internet e, a partir de 2012, o superior de Formação de Professores na modalidade de Ensino a Distância (EaD).'),
        createElement('p',null,'O IFSP é organizado em diversos câmpus e possui mais de 40 mil alunos matriculados nas 36 unidades distribuídas pelo estado de São Paulo.;'),
        createElement('p',null,'Localizado em ',
            createElement('strong',null,'Av. Mutinga, 951 - Jardim Santo Elias, São Paulo - SP - Brasil, 05110-000'))
    );

    raiz.render(conteudo);