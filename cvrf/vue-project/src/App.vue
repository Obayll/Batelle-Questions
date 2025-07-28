<template>
  <div>
    <h1>Vulnerability Search</h1>
    <!-- store textbox information into query variable  -->
    <input v-model="query" type="text" placeholder="Search for vulnerabilities..."/>

    <!-- call getResults() on button click  -->
    <button @click="getResults">Search</button>

    <!--
      if queryResults has any entries
      loop through array (should be length 1)
      if entry is reserved, print out an error and do not print out data
      print out matched index and JSON dump
      else print no items found
    -->
    <div v-if="queryResults.length">
      <div v-for="(item, idx) in queryResults" :key="idx">
        <div v-if="item.reserved">
          <p style="color: red;">Error: Cannot access reserved vulnerability.</p>
        </div>
        <div v-else>
          <h2>Match at index: {{ item.index }}</h2>
          <pre>{{ item.data }}</pre>
        </div>
      </div>
    </div>

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

function isReserved(notes) {
  // If notes is empty, or contains no elements, return false
  if (!notes || !notes.Note) return false

  // Normalize notes as an array
  const notesArray = Array.isArray(notes.Note) ? notes.Note : [notes.Note]

  // Return true if substring '** RESERVED **' exists in __text; else false
  return notesArray.some(note => note.__text.includes('** RESERVED **'))
}

async function getResults() {
  // Always reset queryResults to empty upon function enter
  queryResults.value = []

  // Get user-input from textbox, removing extra whitespace, and convert to lower case
  const cleanQuery = query.value.trim().toLowerCase()

  // If query contains nothing return early
  if (!cleanQuery) {
    return
  }

  // Get response from json-server REST API
  const response = await fetch('http://localhost:3000/cvrfdoc')

  // Convert query response to JSON format
  const responseJSON = await response.json()

  // Get vulnerabilities from top-level API call
  // fetch('http://localhost:3000/cvrfdoc/Vulnerability') does not work since json-server only supports top-level API calls
  const responseVuln = responseJSON.Vulnerability

  // Takes an array of vulnerabilities and maps the data to an explicit index
  // Then filters the data based on the underlying title to an exact match against the user-input
  queryResults.value = responseVuln.map((vuln, index) => ({ index, data: vuln, reserved: isReserved(vuln.Notes) }))
    .filter(({ data }) => data.Title.toLowerCase() == cleanQuery)
}
</script>
