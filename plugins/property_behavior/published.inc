<?php

/**
 * @file
 * published property_behavior plugin for eck.
 */

$plugin = array(
  'label' => t('Published'),
  'default_widget' => 'eck_behavior_published_property_default_widget',
  'entity_view' => 'eck_behavior_published_property_entity_view',
);

/**
 * Implements 'default_widget'.
 */
function eck_behavior_published_property_default_widget($property, $vars) {
  $entity = $vars['entity'];

  if (isset($entity->is_new) && $entity->is_new) {
    $published = ECK_PUBLISHED_DEFAULT_VALUE;
  }
  else {
    $published = isset($entity->{$property}) ? $entity->{$property} : ECK_PUBLISHED_DEFAULT_VALUE;
  }

  return array(
    '#type' => 'checkbox',
    '#title' => $vars['properties'][$property]['label'],
    '#default_value' => $published,
    '#weight' => 99
  );
}

/**
 * Implements 'entity_view'.
 */
function eck_behavior_published_property_entity_view($property, $vars) {
  $entity = $vars['entity'];
  if ($entity->{$property} == ECK_NOT_PUBLISHED_VALUE) {
    if(isset($entity->title)) {
      $entity->title .= ' (Unpublished)';
    }
    drupal_set_title($entity->title);
    if (!user_access('eck administer ' . $entity->entityType() . ' ' . $entity->bundle() . ' entities')) {
      drupal_access_denied();
      drupal_exit();
    }
  }
}

