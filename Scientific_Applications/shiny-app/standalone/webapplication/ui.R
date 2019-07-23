## ui.R ##

# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

library(shinydashboard)

header <- dashboardHeader(title = "Red Hat Tech Exchange 2019",
                          titleWidth = 250,
                          tags$li(class = "dropdown",
                                  tags$a(href = "https://www.redhat.com/", 
                                         target = "_blank", 
                                         tags$img(height = "20px", 
                                                  src = "redhat.png")
                                  )
                          )
                          )

sidebar <- dashboardSidebar(
  width = 250,
  br(),
  sidebarMenu(
      width = 200,
      selectInput("choice", "Products:", choices = products),
      hr(),
      sliderInput("freq",
                  "Minimum word frecuency:",
                  min = 1,  max = 50, value = 10),
      sliderInput("max",
                  "Maximum number of words:",
                  min = 1,  max = 200,  value = 50),
    
    tags$hr()
    )
)

body <- dashboardBody(
    plotOutput("plot")
)

dashboardPage(
  skin="red",
  header,
  sidebar,
  body
)
