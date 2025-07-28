<template>
  <div>
    <h1>Fruit Search</h1>
    <!-- store textbox information into query variable  -->
    <input v-model="query" type="text" placeholder="Search for fuits:"/>

    <!-- call getResults() on button click  -->
    <button @click="getResults">Search</button>

    <!--
      if queryResults has any entries
      loop through queryResults and display the name value
      else print no items found
    -->
    <ul v-if="queryResults.length">
      <li v-for="item in queryResults" :key="item.id">{{ item.name }}</li>
    </ul>
    <p v-else>No results found.</p>
  </div>
</template>

<!-- JavaScript (TypeScript?) block -->
<script setup>

// Use Vue's reactive variable (auto-refresh UI when changed)
import { ref } from 'vue'

// Creates reactive variables for storing the query and query results
// Make sure to store array values under array.value, not array
const query = ref('')
const queryResults = ref([])

async function getResults() {
  // Get user-input from textbox, removing extra whitespace, and convert to lower case
  const cleanQuery = query.value.trim().toLowerCase()

  // If query contains nothing, set queryResults to nothing and return early
  if (!cleanQuery) {
    queryResults.value = []
    return
  }

  // Get response from json-server REST API
  const response = await fetch('http://localhost:3000/items')

  // Convert query response to JSON format
  const responseJSON = await response.json()

  // Iterate through JSON reponse and only keep entries with names containing a substring of the user-input
  queryResults.value = responseJSON.filter(item => item.name.toLowerCase().includes(cleanQuery))
}
</script>
