# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

server <- function(input, output) {

  output$plot <- renderPlot(height = "auto",{
    
    # delete data files, if any, just to download from ceph
    clicmd <- "rm -f *txt.gz"
    system(clicmd)
    
    if ( input$choice == "ceph")
      filename <- "ceph.txt.gz"
    else if ( input$choice == "osp" )
      filename <- "osp.txt.gz"
    else if ( input$choice == "ocp" )
      filename <- "ocp.txt.gz"
    else if ( input$choice == "rhv" )
      filename <- "rhv.txt.gz"
    else if ( input$choice == "ansible" )
      filename <- "ansible.txt.gz"
    
    # download data file from ceph
    clicmd <- paste('python s3downloadfile.py', filename, sep=' ')
    system(clicmd)
    
    words <- termMatrix(input$choice)
    wordcloud_rep <- repeatable(wordcloud)
    wordcloud_rep(names(words), words, 
                  scale=c(3,1),
                  min.freq = input$freq, max.words=input$max,
                  colors=brewer.pal(8, "Dark2"))
    
  })

}
