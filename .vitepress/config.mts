import { defineConfig } from 'vitepress'

export default defineConfig({
  title: "Benchmarking and Optimising the AMAT model",
  description: "Report and Analysis",
  markdown: {
    math: true
  },
  themeConfig: {
    nav: [
      { text: 'Home', link: '/' }
    ],
    sidebar: [
      {
        text: 'Report Sections',
        items: [
          { text: 'Abstract', link: '/#abstract' },
          { text: 'NESTML Pipeline', link: '/#the-nestml-code-generation-pipeline' },
          { text: 'AMAT Model', link: '/#the-amat-neuron-model' },
          { text: 'Network Benchmarking', link: '/#large-scaling-network-benchmarking' },
          { text: 'ODE-toolbox & CSE', link: '/#ode-toolbox-and-common-subexpression-elimination' },
          { text: 'Discussion', link: '/#discussion-and-future-work' }
        ]
      }
    ]
  }
})